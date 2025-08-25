-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Section: NEE
-- Date: 06/02/2024
-- Purpose: Lab 04 DBS211
-- ***********************

SET AUTOCOMMIT ON;

CREATE TABLE MOVIES_aabdelgadir (
    m_id int PRIMARY KEY,
    title varchar(35) NOT NULL,
    release_year int NOT NULL,
    director int NOT NULL,
    score decimal(3,2) CHECK (score > 0 AND score < 5)
);

CREATE TABLE DIRECTORS_aabdelgadir (
    director_id int PRIMARY KEY,
    first_name varchar(20) NOT NULL,
    last_name varchar(30) NOT NULL
);

-- Q2 Solution 

ALTER TABLE MOVIES_aabdelgadir
ADD CONSTRAINT fk_director
FOREIGN KEY (director)
REFERENCES DIRECTORS_aabdelgadir(director_id);

-- Q3 Solution 

ALTER TABLE MOVIES_aabdelgadir
ADD CONSTRAINT unique_title
UNIQUE (title);

-- Q4a Solution

INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name)
VALUES
(9801, 'Rob', 'Minkoff');

INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name)
VALUES
(9802, 'Bill', 'Condon');

INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name)
VALUES
(9803, 'Josh', 'Cooley');

-- Q4b Solution 

INSERT INTO MOVIES_aabdelgadir (m_id, title, release_year, director, score)
VALUES
(801, 'The Lion King', 2019, 9801, 3.50);

INSERT INTO MOVIES_aabdelgadir (m_id, title, release_year, director, score)
VALUES
(802, 'Beauty and the Beast', 2017, 9802, 4.20);

INSERT INTO MOVIES_aabdelgadir (m_id, title, release_year, director, score)
VALUES
(803, 'Toy Story 4', 2019, 9803, 4.50);

-- Q5 Solution
DELETE FROM MOVIES_aabdelgadir;
DELETE FROM DIRECTORS_aabdelgadir;

-- Q6 Solution
DROP TABLE DIRECTORS_aabdelgadir;
 
CREATE TABLE DIRECTORS_aabdelgadir(
  director_id int PRIMARY KEY,
  first_name varchar(20) NOT NULL,
  last_name varchar(30) NOT NULL
);   

-- Q7 SOLUTION
INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name) VALUES ('01', 'Rob', 'Minkoff');
INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name) VALUES ('02', 'Bill', 'Condon');
INSERT INTO DIRECTORS_aabdelgadir (director_id, first_name, last_name) VALUES ('03', 'Josh', 'Cooley');

--Q8 SOLUTION
INSERT INTO DIRECTORS_aabdelgadir  (director_id, first_name, last_name) VALUES ('04', 'Abdalla', 'Abdelgadir');

--Q9 SOLUTION
ALTER TABLE DIRECTORS_aabdelgadir
ADD mobile_phone_no integer;

--Q10 SOLUTION
SELECT * FROM DIRECTORS_aabdelgadir;

--Q11 SOLUTION
UPDATE DIRECTORS_aabdelgadir
SET mobile_phone_no = '1234567890'
WHERE director_id = '04';

--Q12 SOLUTION
DELETE FROM DIRECTORS_aabdelgadir
WHERE director_id = '04';

--Q13 SOLUTION
ALTER TABLE DIRECTORS_aabdelgadir
ADD email_address varchar(200);

UPDATE DIRECTORS_aabdelgadir
SET email_address = last_name || ' ' || first_name || ' ' || director_id || '@seneca.ca';


