CREATE OR REPLACE FUNCTION validate_member_exists()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
  IF NOT EXISTS (SELECT 1 FROM member WHERE member_id = NEW.member_id) THEN
    RAISE EXCEPTION 'Member with ID % does not exist.', NEW.member_id;
  END IF;

  RETURN NEW;
END;
$BODY$;

CREATE TRIGGER trigger_validate_member_exists
BEFORE INSERT
ON checkin
FOR EACH ROW
EXECUTE FUNCTION validate_member_exists();

CREATE OR REPLACE FUNCTION validate_checkin_status()
RETURNS TRIGGER AS $$
BEGIN
  IF EXISTS (SELECT 1 FROM currently_checked_in_members WHERE member_id = NEW.member_id) THEN
    RAISE EXCEPTION 'Member with ID % is already checked in', NEW.member_id;
  END IF;

  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_validate_checkin_status
BEFORE INSERT
ON checkin
FOR EACH ROW
EXECUTE FUNCTION validate_checkin_status();

CREATE OR REPLACE FUNCTION checkin_check_time()
RETURNS TRIGGER AS $$
DECLARE 
    hours_per_day INTERVAL;
    used_hours INTERVAL;
    last_visit_date_old DATE;
BEGIN
    BEGIN
        SELECT last_visit_date INTO last_visit_date_old
        FROM member
        WHERE NEW.member_id = member.member_id;

        IF last_visit_date_old < DATE(NEW.checkin_time) THEN
            UPDATE member
            SET gym_hours_used = INTERVAL '0 hours',
                pool_hours_used = INTERVAL '0 hours',
                last_visit_date = DATE(NEW.checkin_time)
            WHERE member.member_id = NEW.member_id;
        END IF;

        CASE
            WHEN NEW.gym_or_pool = 'gym' THEN
                SELECT gym_hours_used
                INTO used_hours
                FROM member
                WHERE NEW.member_id = member.member_id;

                SELECT total_gym_hours
                INTO hours_per_day
                FROM member_hours_summary
                WHERE NEW.member_id = member_hours_summary.member_id;

            WHEN NEW.gym_or_pool = 'pool' THEN
                SELECT pool_hours_used
                INTO used_hours
                FROM member
                WHERE NEW.member_id = member.member_id;

                SELECT total_pool_hours
                INTO hours_per_day
                FROM member_hours_summary
                WHERE NEW.member_id = member_hours_summary.member_id;

            ELSE
                RAISE EXCEPTION 'Invalid value. Must be either "gym" or "pool".';
        END CASE;

        IF used_hours >= hours_per_day THEN
            RAISE EXCEPTION 'Not enough time left for member_id=%, used_hours=%, hours_per_day=%',
                NEW.member_id, used_hours, hours_per_day;
        END IF;
        
    EXCEPTION
        WHEN OTHERS THEN
            RAISE NOTICE 'Error in checkin_check_time: %', SQLERRM;
            RETURN NULL;
    END;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_check_time
BEFORE INSERT
ON checkin
FOR EACH ROW
EXECUTE FUNCTION checkin_check_time();

CREATE OR REPLACE FUNCTION calculate_late_fee()
RETURNS TRIGGER AS $$
DECLARE
    minutes_overstay INTEGER;
    late_fee DECIMAL(10, 2);
    grace_period INTEGER := 15;
BEGIN
    minutes_overstay := EXTRACT(EPOCH FROM (NEW.checkout_time - NEW.checkin_time)) / 60;
    CASE
        WHEN NEW.gym_or_pool = 'gym' THEN
            minutes_overstay = minutes_overstay - member_hours_summary.total_gym_hours;
        WHEN NEW.gym_or_pool = 'pool' THEN
            minutes_overstay  = minutes_overstay - member_hours_summary.total_pool_hours;
    END CASE;

    IF minutes_overstay > grace_period THEN
        minutes_overstay := minutes_overstay - grace_period;
    ELSE
        minutes_overstay := 0;
    END IF;

    SELECT overstay_fee_per_minute INTO late_fee
    FROM location
    WHERE location_id = NEW.location_id;

    late_fee := late_fee * minutes_overstay;

    UPDATE checkin
    SET overstay_fee = late_fee
    WHERE checkin_id = NEW.checkin_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER late_fee_trigger
AFTER UPDATE OF checkout_time ON checkin
FOR EACH ROW
WHEN (NEW.checkout_time IS NOT NULL AND NEW.checkin_time < NEW.checkout_time)
EXECUTE FUNCTION calculate_late_fee();

CREATE OR REPLACE FUNCTION update_time_spent()
RETURNS TRIGGER AS $$
DECLARE 
	hours_spent INTERVAL;
BEGIN

    hours_spent := NEW.checkout_time - NEW.checkin_time;
    CASE
        WHEN NEW.gym_or_pool = 'gym' THEN
            UPDATE member
            SET 
                gym_hours_used = COALESCE(gym_hours_used, '0 hours') + hours_spent,
                last_visit_date = DATE(NEW.checkin_time)
            WHERE member_id = NEW.member_id;

        WHEN NEW.gym_or_pool = 'pool' THEN
            UPDATE member
            SET 
                pool_hours_used = COALESCE(pool_hours_used, '0 hours') + hours_spent,
                last_visit_date = DATE(NEW.checkin_time)
            WHERE member_id = NEW.member_id;

        ELSE
            RAISE EXCEPTION 'Invalid value. Must be either "gym" or "pool".';
    END CASE;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER checkout_trigger
AFTER UPDATE OF checkout_time ON checkin
FOR EACH ROW
WHEN (NEW.checkout_time IS NOT NULL)
EXECUTE FUNCTION update_time_spent();
