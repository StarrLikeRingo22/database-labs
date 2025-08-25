-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 1137374198
-- Section: NEE
-- Date: 02/13/2024
-- Purpose: Lab 05 DBS211
-- ***********************

SET AUTOCOMMIT ON;

-- Question 1: ANSI-92 Join
SELECT emp.employeenumber
, emp.firstname
, emp.lastname
, o.city
, o.phone
, o.postalcode
, o.country
from dbs211_employees emp
join dbs211_offices o
    on emp.officecode = o.officecode
WHERE o.country = 'france';

-- Question 1: ANSI-89 Join
select emp.employeenumber
, emp.firstname
, emp.lastname
, o.city
, o.phone
, o.postalcode
, o.country
from dbs211_employees emp ,  dbs211_offices o 
where emp.officecode = o.officecode and (o.country = 'France');


-- Question 2
select *
from dbs211_payments pay
join dbs211_customers cus   
    on pay.customernumber = cus.customernumber;
    
-- Question 3
SELECT c.customerNumber, c.customerName
FROM dbs211_customers c
LEFT JOIN dbs211_payments p ON c.customerNumber = p.customerNumber
WHERE p.customerNumber IS NULL
AND c.country = CASE
    WHEN MOD(8, 2) = 0 THEN 'USA'
    ELSE 'Canada'
END
ORDER BY c.customerNumber;

-- Question 4a
CREATE VIEW vwCustomerOrder113734198 as
SELECT cus.CustomerNumber, ord.OrderNumber,  ord.OrderDate, pro.ProductName, detord.QuantityOrdered, detord.PriceEach AS Price
FROM dbs211_customers cus
JOIN dbs211_orders ord ON cus.CustomerNumber = ord.CustomerNumber
JOIN dbs211_orderdetails detord ON ord.OrderNumber = detord.OrderNumber
JOIN dbs211_products pro ON detord.ProductCode = pro.ProductCode;

-- Q4 SOLUTION B 
SELECT * FROM vwCustomerOrder113734198;

-- Q5 SOLUTION
SELECT *
FROM vwCustomerOrderSenecaStudentID
WHERE CustomerNumber = 124 + (MOD(1137374198, 10))
ORDER BY orderNumber, orderLineNumber;

-- Q6 SOLUTION
SELECT 
    cus.CustomerNumber,
    cus.ContactFirstName,
    cus.ContactLastName,
    cus.Phone,
    cus.CreditLimit
FROM dbs211_customers cus
LEFT JOIN dbs211_orders ord ON cus.CustomerNumber = ord.CustomerNumber
WHERE ord.OrderNumber IS NULL;

-- Q7 SOLUTION
CREATE VIEW vwEmployeeManageraabdelgadir AS
SELECT 
    e.EMPLOYEENUMBER AS EmployeeID,
    e.FIRSTNAME AS EmployeeFirstName,
    e.LASTNAME AS EmployeeLastName,
    e.EMAIL AS EmployeeEmail,
    e.EXTENSION AS EmployeeExtension,
    e.OFFICECODE AS EmployeeOfficeCode,
    e.JOBTITLE AS EmployeeJobTitle,
    m.FIRSTNAME AS ManagerFirstName,
    m.LASTNAME AS ManagerLastName
FROM 
    dbs211_employees e
LEFT JOIN 
    dbs211_employees m ON e.REPORTSTO = m.EMPLOYEENUMBER;

-- Q8 SOLUTION
CREATE OR REPLACE VIEW vwEmployeeManageraabdelgadir AS
SELECT 
    e.EMPLOYEENUMBER AS EmployeeID,
    e.FIRSTNAME AS EmployeeFirstName,
    e.LASTNAME AS EmployeeLastName,
    e.EMAIL AS EmployeeEmail,
    e.EXTENSION AS EmployeeExtension,
    e.OFFICECODE AS EmployeeOfficeCode,
    e.JOBTITLE AS EmployeeJobTitle,
    m.FIRSTNAME AS ManagerFirstName,
    m.LASTNAME AS ManagerLastName
FROM 
    dbs211_employees e
JOIN 
    dbs211_employees m ON e.REPORTSTO = m.EMPLOYEENUMBER
WHERE 
    e.REPORTSTO IS NOT NULL;

-- Q9 SOLUTION
DROP VIEW vwCustomerOrder113734198;
DROP VIEW vwEmployeeManageraabdelgadir;