-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Section: NEE
-- Date: 03/12/2024
-- Purpose: Lab 07 DBS211
-- ***********************


--Question 2
CREATE TABLE aabdelgadiremployees_113734198 (
    EMPLOYEENUMBER NUMBER(38,0) NOT NULL,
    LASTNAME VARCHAR2(50 BYTE) NOT NULL,
    FIRSTNAME VARCHAR2(50 BYTE) NOT NULL,
    EMAIL VARCHAR2(100 BYTE) NOT NULL,
    EXTENSION VARCHAR2(10 BYTE) NOT NULL,
    OFFICECODE VARCHAR2(10 BYTE) NOT NULL,
    REPORTSTO NUMBER(38,0),
    JOBTITLE VARCHAR2(50 BYTE) NOT NULL,
    CONSTRAINT pk_employee PRIMARY KEY (EMPLOYEENUMBER)
);
SELECT * FROM dbs211_employees WHERE 1 = 2;

--Question 3
SET AUTOCOMMIT OFF;
SET TRANSACTION READ WRITE;

--Question 4

INSERT INTO aabdelgadiremployees_113734198 (employee_id, last_name, first_name, job_title, reports_to, hire_date, salary, commission_pct, department_id)
SELECT employee_id, last_name, first_name, job_title, NULL, hire_date, salary, commission_pct, department_id
FROM DBS211_Employees
WHERE ROWNUM <= FLOOR(DBMS_RANDOM.VALUE(50, 201)); 
--Question 5
SELECT *
FROM aabdelgadiremployees_113734198;

--Question 6
ROLLBACK;
SELECT *
FROM aabdelgadiremployees_113734198;

--Question 7
INSERT INTO aabdelgadiremployees_113734198 (employee_id, last_name, first_name, job_title, reports_to, hire_date, salary, commission_pct, department_id)
SELECT employee_id, last_name, first_name, job_title, NULL, hire_date, salary, commission_pct, department_id
FROM DBS211_Employees
WHERE ROWNUM <= FLOOR(DBMS_RANDOM.VALUE(50, 201));
SELECT *
FROM aabdelgadiremployees_113734198;

--Question 8
UPDATE aabdelgadiremployees_113734198
SET jobTitle = 'unknown';

--Question 9
COMMIT;

--Question 10a
ROLLBACK;
--Question 10b
SELECT *
FROM aabdelgadiremployees_113734198
WHERE jobTitle = 'unknown';

--Question 11
START TRANSACTION;

DELETE FROM aabdelgadiremployees_113734198;

--Question 12
CREATE VIEW viewNewEmps AS
SELECT *
FROM aabdelgadiremployees_113734198
ORDER BY last_name, first_name;

--Question 13
ROLLBACK;

--Question 14
START TRANSACTION;
INSERT INTO aabdelgadiremployees_113734198 (employee_id, last_name, first_name, job_title, reports_to, hire_date, salary, commission_pct, department_id)
SELECT employee_id, last_name, first_name, job_title, NULL, hire_date, salary, commission_pct, department_id
FROM DBS211_Employees
WHERE ROWNUM <= FLOOR(DBMS_RANDOM.VALUE(50, 201)); -- Generates a random number between 50 and 200 for the number of rows

--Question 15
SAVEPOINT insertion113734198;

--Question 16
UPDATE aabdelgadiremployees_113734198
SET job_title = 'unknown';
SELECT *
FROM aabdelgadiremployees_113734198;

--Question 17
ROLLBACK TO SAVEPOINT insertion113734198;
SELECT *
FROM aabdelgadiremployees_113734198;

--Question 18
ROLLBACK;
SELECT *
FROM aabdelgadiremployees_113734198;
