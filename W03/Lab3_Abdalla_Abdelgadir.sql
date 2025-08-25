-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Date: 30/01/2024
-- Purpose: Lab 03 DBS211
-- ***********************
SET AUTOCOMMIT ON;
drop table PART;
drop table PART_aabdelgadir_113734198;

create table PART_aabdelgadir_113734198(
   part_number varchar2(20) not null,
   part_desc varchar(255),
   on_hand integer not null,
   class varchar(10),
   warehouse integer,
   price FLOAT not null
);   



truncate table PART_aabdelgadir_113734198;
insert into PART_aabdelgadir_113734198 values ('AX12', 'Iron', 104, 'HW', 3, 23.95);
insert into PART_aabdelgadir_113734198 values ('AZ52', 'Dartboard', 20, 'SG', 2, 12.95);
insert into PART_aabdelgadir_113734198 values ('BA74', 'Basketball', 40, 'SG', 1, 29.95);
insert into PART_aabdelgadir_113734198 values ('BH22', 'Cornpopper', 95, 'HW', 3, 24.95);
insert into PART_aabdelgadir_113734198 values ('BT04', 'Gas Grill', 11, 'AP', 2, 149.99);
insert into PART_aabdelgadir_113734198 values ('BZ66', 'Washer', 52, 'AP', 3, 399.99);
insert into PART_aabdelgadir_113734198 values ('CA14', 'Griddle', 78, 'HW', 3, 39.99);
insert into PART_aabdelgadir_113734198 values ('CB03', 'Bike', 44, 'SG', 1, 299.99);
insert into PART_aabdelgadir_113734198 values ('CX11', 'Blender', 112, 'HW', 3, 22.95);
insert into PART_aabdelgadir_113734198 values ('CZ81', 'Treadmill', 68, 'SG', 2, 349.99);

select *
from PART_aabdelgadir_113734198;

-- Question 1
SELECT part_number
    FROM PART_aabdelgadir_113734198;
 
-- Question 2   
SELECT *
    FROM PART_aabdelgadir_113734198;

-- Question 3
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE on_hand > 90;
    
-- Question 4  
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE part_number = 'AX12';
    
-- Question 5
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE on_hand > 90
    ORDER BY on_hand;
    
-- Question 6
SELECT *
    FROM PART_aabdelgadir_113734198
    ORDER BY class, on_hand;
    
-- Question 7
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE class IN('HW', 'AP');

SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE warehouse IN(1, 2);

-- Question 8 
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE price 
    BETWEEN 10 AND 50;
    
SELECT *
    FROM PART_aabdelgadir_113734198
    WHERE part_number 
    BETWEEN 'BA' AND 'CA';

-- Question 9
SELECT * 
    FROM PART_aabdelgadir_113734198
    WHERE price IS NULL;

SELECT * 
    FROM PART_aabdelgadir_113734198 
    WHERE price IS NOT NULL;
    
-- Question 10
SELECT * 
    FROM PART_aabdelgadir_113734198 
    WHERE class LIKE 'HW';

-- Question 11
SELECT * 
    FROM PART_aabdelgadir_113734198 
    WHERE part_desc LIKE 'B%';

-- Question 12
SELECT * 
    FROM PART_aabdelgadir_113734198 
    WHERE upper(part_desc) LIKE '%D';

-- Question 13
SELECT * 
    FROM PART_aabdelgadir_113734198 
    WHERE lower(part_desc) LIKE '%pop%';

-- Question 14a
INSERT INTO
    PART_aabdelgadir_113734198(part_desc, part_number, on_hand, class, warehouse, price)
    VALUES 
    ('Soccer Ball', 'RC16', 26, 'SG', 1, 24.95);

-- Question 14b   
INSERT INTO PART_aabdelgadir_113734198
   VALUES
   ('RC16', 'Soccer Ball', 26, 'SG', 1, 24.95);

-- Question 15   
UPDATE PART_aabdelgadir_113734198 SET 
    part_desc = 'Gas/Propane Grill'
    WHERE part_number = 'BT04';
    
UPDATE PART_aabdelgadir_113734198 SET
    price = price * 1.10
    WHERE class = 'SG';

-- Question 16
DELETE FROM PART_aabdelgadir_113734198
    WHERE part_number = 'BT04';

DELETE FROM PART_aabdelgadir_113734198
    Where warehouse = 2;