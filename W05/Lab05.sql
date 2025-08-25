-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Date: 12/07/2024      
-- Purpose: Lab 5 DBS311
-- ***********************

SET SERVEROUTPUT ON; 
SET PAGESIZE 120;
CREATE OR REPLACE PROCEDURE Even_Odd (value IN INT) AS    
BEGIN   
IF MOD(value,2) =0 THEN     
 DBMS_OUTPUT.PUT_LINE ('The number is even');   
ELSE    
 DBMS_OUTPUT.PUT_LINE ('The number is odd');   
END IF;   
END;
/
DECLARE
 value INT :=100; 
BEGIN   
  Even_Odd(value);
END; -- Q1 SOLUTION
/
DECLARE
 value INT :=99;  
BEGIN   
  Even_Odd(value);
END; -- Q1 SOLUTION

CREATE OR REPLACE PROCEDURE Find_Employee (employeeID NUMBER) AS
  firstName VARCHAR2(255 BYTE);
  lastName VARCHAR2(255 BYTE);
  email VARCHAR2(255 BYTE);
  phone VARCHAR2(255 BYTE);
  hairDate VARCHAR2(255 BYTE);
  jobTitle VARCHAR2(255 BYTE);
BEGIN
  SELECT first_name, last_name,email,phone,hire_date,job_title INTO firstName, lastName, email,phone,hairDate,jobTitle
  FROM employees
  WHERE employee_id = employeeID;
  DBMS_OUTPUT.PUT_LINE ('First name: ' || firstName);
  DBMS_OUTPUT.PUT_LINE ('Last name: ' || lastName);
  DBMS_OUTPUT.PUT_LINE ('Email: ' || email);
  DBMS_OUTPUT.PUT_LINE ('Phone: ' || phone);
  DBMS_OUTPUT.PUT_LINE ('Hire date: ' || hairDate);
  DBMS_OUTPUT.PUT_LINE ('Job title: ' || jobTitle);
EXCEPTION
WHEN OTHERS
  THEN 
      DBMS_OUTPUT.PUT_LINE ('Error!');
END;
/
DECLARE
 ID NUMBER :=107;  
BEGIN   
  Find_Employee(ID);
END;
/
DECLARE
 ID NUMBER :=99999;  
BEGIN   
  Find_Employee(ID);
END; -- Q2 Solution

CREATE OR REPLACE PROCEDURE Update_Price_by_Cat (id products.category_id%type,amount NUMBER) AS
Rows_updated NUMBER;
BEGIN
   UPDATE PRODUCTS SET List_price = List_price + amount
   WHERE CATEGORY_ID = id
  AND   LIST_PRICE > 0;
        Rows_updated := sql%rowcount;
  IF (Rows_updated = 0) then
        DBMS_OUTPUT.PUT_LINE ('Invalid Category ID');
  ELSE 
        DBMS_OUTPUT.PUT_LINE ('The number of updated rows is: ' || Rows_updated);
  END IF; 
EXCEPTION
WHEN OTHERS
  THEN 
      DBMS_OUTPUT.PUT_LINE ('Error!');
END; 
/
DECLARE
     A NUMBER :=1;
     B NUMBER :=5;
    BEGIN
      Update_Price_by_Cat (A,B);
   END; -- Q3 solution
/
DECLARE  
     A NUMBER :=99999;
     B NUMBER :=5;
    BEGIN
      Update_Price_by_Cat (A,B);
   END;
/
ROLLBACK;

--Q4 Solution
CREATE OR REPLACE PROCEDURE Update_Price_Under_Avg AS
AvgPrice products.list_price%type;
updatedRows NUMBER;
BEGIN
SELECT avg(list_price) INTO AvgPrice
FROM products;

IF(AvgPrice<=1000) THEN
UPDATE products SET products.list_price=products.list_price* 1.02
WHERE list_price<avgPrice;
updatedRows := SQL%ROWCOUNT;
DBMS_OUTPUT.PUT_LINE ('Rows_updated ' || updatedRows);
END IF
EXCEPTION
WHEN OTHERS
THEN
DBMS_OUTPUT.PUT_LINE('Error!');
END;
--Q5 Solution
CREATE OR REPLACE PROCEDURE Product_Price_Report AS
price products.list_price%type;
avg_price products.list_price%type;
min_price products.list_price%type;
max_price products.list_price%type;
cheap_count NUMBER;
fair_count NUMBER;
exp_count NUMBER;
calc1 float;
calc2 float;

BEGIN
SELECT avg(list_prices), MAX(list_prices) MIN(list_prices) INTO avg_price, max_price, min_price
FROM products;

calc1:= (avg_price - min_price) /2;
calc2:= (avg_price - min_price) /2;

SELECT count(*) INTO fair_count
FROM products
WHERE list_price < calc1;
DSBM_OUTPUT.PUJT_LINE('CHEAP: ' || cheap_count);
