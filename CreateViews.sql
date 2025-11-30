CREATE OR REPLACE VIEW currently_checked_in_members AS
SELECT
    m.member_id,
    m.name,
    m.surname,
    c.checkin_time,
    l.title AS location,
    c.gym_or_pool,
    AGE(NOW(), c.checkin_time) AS time_since_checkin
FROM
    checkin c
    JOIN member m ON c.member_id = m.member_id
    JOIN location l ON c.location_id = l.location_id
WHERE
    c.checkout_time IS NULL;

CREATE OR REPLACE VIEW member_membership_info AS
SELECT
    m.member_id,
    m.name,
    m.surname,
    m.dob,
    mm.membership_id,
    mem.title AS membership_title,
    mem.gym_hours,
    mem.pool_hours,
    mem.month_price,
    mm.bought_on,
    mm.duration_in_months,
    (mm.bought_on + (mm.duration_in_months || ' months')::INTERVAL)::DATE AS expiration_date
    FROM
    member m
    JOIN member_membership mm ON m.member_id = mm.member_id
    JOIN membership mem ON mm.membership_id = mem.membership_id;

CREATE MATERIALIZED VIEW member_hours_summary AS
SELECT
    m.member_id,
    m.name,
    m.surname,
    COALESCE(SUM(CASE WHEN CURRENT_DATE <= (mm.bought_on + (mm.duration_in_months || ' months')::INTERVAL) THEN mem.pool_hours ELSE '0 hours' END), '0 hours') AS total_pool_hours,
    COALESCE(SUM(CASE WHEN CURRENT_DATE <= (mm.bought_on + (mm.duration_in_months || ' months')::INTERVAL) THEN mem.gym_hours ELSE '0 hours' END), '0 hours') AS total_gym_hours
FROM
    member m
LEFT JOIN
    member_membership mm ON m.member_id = mm.member_id
LEFT JOIN
    membership mem ON mm.membership_id = mem.membership_id
GROUP BY
    m.member_id, m.name, m.surname;

REFRESH MATERIALIZED VIEW member_hours_summary;

CREATE INDEX idx_member_hours_summary_member_id ON member_hours_summary(member_id);