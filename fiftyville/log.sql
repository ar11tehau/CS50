-- Keep a log of any SQL queries you execute as you solve the mystery.

--Get the report on the 28/07/2021
SELECT description FROM crime_scene_reports
WHERE (year=2021 AND month=07 AND day=28);

--Get the interviews on the 28/07/2021
SELECT name, transcript FROM interviews
WHERE (year=2021 AND month=07 AND day=28);

--Get atm transactions locations
SELECT atm_location FROM atm_transactions ORDER BY atm_locations;

--Get atm transactions_type locations
--SELECT transaction_type FROM atm_transactions ORDER BY transaction_type;

--Get withdraw amount and accound_number from "Humphrey Lane" on the 28/07/2021
SELECT amount, account_number FROM atm_transactions
WHERE (year=2021 AND month=07 AND day=28 AND atm_location="Humphrey Lane" AND transaction_type="withdraw")
ORDER BY amount DESC;

--Get Fiftyville airport id
SELECT id FROM airports
WHERE city="Fiftyville";

--Get first flight id on the 29/07/2021
SELECT flights.id FROM flights
INNER JOIN airports ON airports.id=destination_airport_id
WHERE year=2021 AND month=07 AND day=29
AND origin_airport_id=(SELECT id FROM airports WHERE abbreviation="CSF")
ORDER BY hour LIMIT 1;

--Get name and license plate from the bakery security logs on the 28/07/2021 afrom 10:15 to 10:25
SELECT people.name, bakery_security_logs.license_plate, minute FROM bakery_security_logs
INNER JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE year=2021 AND month=07 AND day=28 AND hour=10 AND minute>15 AND minute<25
ORDER BY minute;

--Get the caller and receiver name on the 28/07/2021 lesser than 60s
SELECT caller_people.name, receiver_people.name FROM phone_calls
INNER JOIN people AS caller_people ON caller_people.phone_number=caller
INNER JOIN people AS receiver_people ON receiver_people.phone_number=receiver
WHERE year=2021 AND month=07 AND day=28 AND duration<60;

--On the 28/07/2021, get name of the people registered on the bakery security logs (between 10:15 and 10:35), who also withdrawed money from the "Humphrey Lane" atm, who also made a call lesser than 60s and took the first flight on the next day

SELECT people.name FROM bakery_security_logs
INNER JOIN people ON people.license_plate = bakery_security_logs.license_plate
INNER JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE year=2021 AND month=07 AND day=28 AND hour=10 AND minute>15 AND minute<35
AND bank_accounts.account_number IN (SELECT account_number from atm_transactions WHERE year=2021 AND month=07 AND day=28 AND transaction_type="withdraw")
AND people.passport_number IN (SELECT passport_number FROM passengers WHERE passengers.flight_id = (SELECT flights.id FROM flights
INNER JOIN airports ON airports.id=destination_airport_id
WHERE year=2021 AND month=07 AND day=29
AND origin_airport_id=(SELECT id FROM airports WHERE abbreviation="CSF")
ORDER BY hour LIMIT 1))
AND people.name IN (SELECT caller_people.name FROM phone_calls
INNER JOIN people AS caller_people ON caller_people.phone_number=caller
WHERE year=2021 AND month=07 AND day=28 AND duration<60);

