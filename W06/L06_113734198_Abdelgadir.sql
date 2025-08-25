-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Date: 25/07/2024
-- Purpose: Lab 6 DBS311
-- ***********************

-- Q1 SOLUTION –
SET SERVEROUTPUT ON;
SET PAGESIZE 120;

CREATE OR REPLACE PROCEDURE Get_Fact(n INTEGER) AS
factorial INTEGER := 1;

BEGIN
    FOR i IN REVERSE 1..n LOOP
        factorial := factorial * i;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE(n || '! = ' || factorial);
END;
/
BEGIN 
Get_Fact(4);
Get_Fact(0);
END;
/

-- Q2 SOLUTION –
CREATE OR REPLACE PROCEDURE Calculate_Salary (empID employee.employee_id%type) AS
    emp employee%rowtype;
    baseSalary employee.salary%type := 10000; 
    newSalary employee.salary%type;
    yearsWorked INTEGER;
BEGIN
    SELECT * INTO emp
    FROM employee
    WHERE employee_id = empID;

    yearsWorked := trunc(MONTHS_BETWEEN(SYSDATE, emp.hire_date) / 12); -- Truncate to avoid rounding up
    
    
    newSalary := baseSalary; 
    FOR year IN 1..yearsWorked LOOP
        newSalary := newSalary * 1.05;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('First Name: ' || emp.first_name);
    DBMS_OUTPUT.PUT_LINE('Last Name: ' || emp.last_name);
    DBMS_OUTPUT.PUT_LINE('Annual Salary: $' || to_char(newSalary, '$99,999'));
    
    EXCEPTION WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Employee (ID: ' || empID || ') does not exist.');

END;

/
BEGIN
Calculate_Salary(0);
Calculate_Salary(124);
End;
/

-- Q3 SOLUTION –
CREATE OR REPLACE PROCEDURE WAREHOUSES_REPORT ( WarehouseIdIn IN VARCHAR2,
        WAREHOUSE_ID OUT VARCHAR2, WAREHOUSE_NAME OUT VARCHAR2,
        CITY OUT VARCHAR2, STATE OUT VARCHAR2) AS
    
    NumIndex NUMBER := 1;
    mWareID NUMBER;
    ID0 NUMBER;

BEGIN 
    SELECT MAX(WAREHOUSE_ID) INTO mWareID FROM WAREHOUSES;

    WHILE(NumIndex <= mWareID)
        LOOP   
            SELECT A.WAREHOUSE_ID, A.WAREHOUSE_NAME, B.CITY,
                CASE   
                    WHEN B.STATE IS NULL THEN 'no state'
                    ELSE B.STATE
                    END
                INTO WAREHOUSE_ID, WAREHOUSE_NAME, CITY, STATE
                FROM WAREHOUSES A JOIN LOCATIONS B ON A.LOCATION_ID = B.LOCATION_ID
                WHERE WAREHOUSE_ID = NumIndex;
 
                DBMS_OUTPUT.PUT_LINE('Warehouse ID: '||WAREHOUSE_ID );
                DBMS_OUTPUT.PUT_LINE('Warehouse Name: '||WAREHOUSE_NAME );
                DBMS_OUTPUT.PUT_LINE('City: '||CITY);
                DBMS_OUTPUT.PUT_LINE('State: '||STATE);
                DBMS_OUTPUT.PUT_LINE('');

            NumIndex := NumIndex + 1; 
        END LOOP;
END;

/
DECLARE
    Warehouse_Id VARCHAR2(22);
    Warehouse_Name VARCHAR2(22);
    Warehouse_City VARCHAR2(22);
    Warehouse_State VARCHAR2(22);

BEGIN
    WAREHOUSES_REPORT('1',Warehouse_Id, Warehouse_Name,Warehouse_City, Warehouse_State);
END;
/