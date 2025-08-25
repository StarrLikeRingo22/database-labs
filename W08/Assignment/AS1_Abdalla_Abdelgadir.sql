-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 1137374198
-- Section: NEE
-- Date: 03/08/2024
-- Purpose: Assignment 1 DBS211
-- ***********************

SET AUTOCOMMIT ON;

SELECT e.EmployeeNumber, e.FirstName, e.LastName, e.Email, e.JobTitle, o.City
FROM dbs211_employees e
JOIN dbs211_offices o ON e.OfficeCode = o.OfficeCode
WHERE o.Territory = 'NA' AND o.State = 'CA';

ALTER TABLE dbs211_employees
ADD CONSTRAINT chk_email_format CHECK (INSTR(Email, '@') > 0 AND INSTR(Email, '.') > 0);
