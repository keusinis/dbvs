DROP TABLE IF EXISTS address;
CREATE TABLE address (
    address_id SERIAL PRIMARY KEY,
    city VARCHAR(255) NOT NULL,
    street VARCHAR(255) NOT NULL,
    house VARCHAR(15) NOT NULL,
    apartment VARCHAR(15)
);

DROP TABLE IF EXISTS location;

CREATE TABLE location (
    location_id SERIAL PRIMARY KEY,
    address_id INT,
    title VARCHAR(255) NOT NULL,
    overstay_fee_per_minute DECIMAL(10, 2) NOT NULL
);

ALTER TABLE location
    ADD CONSTRAINT fk_location_address
    FOREIGN KEY (address_id)
    REFERENCES address(address_id);

CREATE UNIQUE INDEX idx_unique_adress_id_title ON location (address_id, title);

DROP TABLE IF EXISTS membership;

CREATE TABLE membership (
    membership_id SERIAL PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    gym_hours INTERVAL NOT NULL DEFAULT '0 hours',
    pool_hours INTERVAL NOT NULL DEFAULT '0 hours',
    month_price DECIMAL(10, 2) NOT NULL
);

DROP TABLE IF EXISTS member;

CREATE TABLE member (
    member_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    surname VARCHAR(255) NOT NULL,
    dob DATE NOT NULL,
    address_id INT,
    gym_hours_used INTERVAL DEFAULT INTERVAL '0 hours' CHECK (gym_hours_used >= '0 hours'),
    pool_hours_used INTERVAL DEFAULT INTERVAL '0 hours' CHECK (pool_hours_used >= '0 hours'),
    last_visit_date DATE  DEFAULT NULL,
    CONSTRAINT valid_dob CHECK (dob <= CURRENT_DATE),
    CONSTRAINT valid_last_visit_date CHECK (last_visit_date IS NULL OR last_visit_date <= CURRENT_DATE)
);

ALTER TABLE member
    ADD CONSTRAINT fk_member_address
    FOREIGN KEY (address_id)
    REFERENCES address(address_id);

CREATE INDEX idx_member_name_surname ON member(name, surname);

DROP TABLE IF EXISTS member_membership;

CREATE TABLE member_membership (
    member_id INT,
    membership_id INT,
    bought_on DATE NOT NULL DEFAULT CURRENT_DATE,
    duration_in_months INTEGER NOT NULL,
    PRIMARY KEY (member_id, membership_id),
    CONSTRAINT valid_bought_on CHECK (bought_on <= current_date),
    CONSTRAINT valid_duration_in_months CHECK (duration_in_months >= 0)
);

ALTER TABLE member_membership
    ADD CONSTRAINT fk_member_membership_member
    FOREIGN KEY (member_id)
    REFERENCES member(member_id)
    ON DELETE CASCADE;

ALTER TABLE member_membership
    ADD CONSTRAINT fk_member_membership_membership
    FOREIGN KEY (membership_id)
    REFERENCES membership(membership_id);

DROP TABLE IF EXISTS checkin;

CREATE TABLE checkin (
    checkin_id SERIAL PRIMARY KEY,
    member_id INT,
    checkin_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    checkout_time TIMESTAMP DEFAULT NULL,
    location_id INT,
    gym_or_pool VARCHAR(10) CHECK (gym_or_pool IN ('gym', 'pool')),
    overstay_fee DECIMAL(10, 2) NOT NULL DEFAULT 0,
    CONSTRAINT valid_time CHECK (checkin_time < checkout_time OR checkout_time IS NULL)
);

ALTER TABLE checkin
    ADD CONSTRAINT fk_checkin_member
    FOREIGN KEY (member_id)
    REFERENCES member(member_id);

ALTER TABLE checkin
    ADD CONSTRAINT fk_checkin_location
    FOREIGN KEY (location_id)
    REFERENCES location(location_id) ON DELETE RESTRICT 
                                    ON UPDATE RESTRICT;

CREATE INDEX idx_null_checkout_time ON checkin (checkin_time) WHERE checkout_time IS NULL;