-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 113734198
-- Section: NEE
-- Date: 03/24/2024
-- Purpose: Lab 09 DBS211
-- ***********************

SET AUTOCOMMIT ON;

-- Create Customer Table
CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    Fname VARCHAR(50),
    Lname VARCHAR(50),
    Address VARCHAR(255),
    Phone VARCHAR(20),
    Email VARCHAR(100)
);

-- Insert sample data into Customer Table
INSERT INTO Customer (CustomerID, Fname, Lname, Address, Phone, Email)
VALUES (1, 'John', 'Doe', '123 Main St', '555-1234', 'john@example.com');
INSERT INTO Customer (CustomerID, Fname, Lname, Address, Phone, Email)
VALUES (2, 'Jane', 'Smith', '456 Elm St', '555-5678', 'jane@example.com');
INSERT INTO Customer (CustomerID, Fname, Lname, Address, Phone, Email)
VALUES (3, 'Alice', 'Johnson', '789 Oak St', '555-9012', 'alice@example.com');
INSERT INTO Customer (CustomerID, Fname, Lname, Address, Phone, Email)
VALUES (4, 'Bob', 'Brown', '101 Pine St', '555-3456', 'bob@example.com');
INSERT INTO Customer (CustomerID, Fname, Lname, Address, Phone, Email)
VALUES (5, 'Emily', 'Davis', '222 Cedar St', '555-7890', 'emily@example.com');
    
-- Create OrderHeader Table
CREATE TABLE OrderHeader (
    OrderID INT PRIMARY KEY,
    OrderDate DATE,
    OrderTime TIMESTAMP,
    CustomerID INT,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

-- Insert sample data into OrderHeader Table
INSERT INTO OrderHeader (OrderID, OrderDate, OrderTime, CustomerID)
VALUES (1, TO_DATE('2024-03-24', 'YYYY-MM-DD'), TO_TIMESTAMP('2024-03-24 10:00:00', 'YYYY-MM-DD HH24:MI:SS'), 1);
INSERT INTO OrderHeader (OrderID, OrderDate, OrderTime, CustomerID)
VALUES (2, TO_DATE('2024-03-25', 'YYYY-MM-DD'), TO_TIMESTAMP('2024-03-25 11:30:00', 'YYYY-MM-DD HH24:MI:SS'), 2);
INSERT INTO OrderHeader (OrderID, OrderDate, OrderTime, CustomerID)
VALUES (3, TO_DATE('2024-03-26', 'YYYY-MM-DD'), TO_TIMESTAMP('2024-03-26 12:45:00', 'YYYY-MM-DD HH24:MI:SS'), 3);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (4, TO_DATE('2024-03-27', 'YYYY-MM-DD'), 4);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (5, TO_DATE('2024-03-28', 'YYYY-MM-DD'), 5);
-- Create OrderLine Table
CREATE TABLE OrderLine (
    OrderID INT PRIMARY KEY,
    OrderDate DATE,
    CustomerID INT,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

-- Insert sample data into OrderLine Table
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (1, TO_DATE('2024-03-24', 'YYYY-MM-DD'), 1);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (2, TO_DATE('2024-03-25', 'YYYY-MM-DD'), 2);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (3, TO_DATE('2024-03-26', 'YYYY-MM-DD'), 3);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (4, TO_DATE('2024-03-27', 'YYYY-MM-DD'), 4);
INSERT INTO OrderLine (OrderID, OrderDate, CustomerID)
VALUES (5, TO_DATE('2024-03-28', 'YYYY-MM-DD'), 5);

-- Create Pizza Table
CREATE TABLE Pizza (
    PizzaID INT PRIMARY KEY,
    Name VARCHAR(100),
    Specification VARCHAR(255),
    Price DECIMAL(10, 2)
);

-- Insert sample data into Pizza Table
INSERT INTO Pizza (PizzaID, Name, Specification, Price)
VALUES (1, 'Margherita', 'Tomato, mozzarella, basil', 8.99);
INSERT INTO Pizza (PizzaID, Name, Specification, Price)
VALUES (2, 'Pepperoni', 'Tomato, mozzarella, pepperoni', 9.99);
INSERT INTO Pizza (PizzaID, Name, Specification, Price)
VALUES (3, 'Vegetarian', 'Tomato, mozzarella, mixed vegetables', 10.99);
INSERT INTO Pizza (PizzaID, Name, Specification, Price)
VALUES (4, 'Hawaiian', 'Tomato, mozzarella, ham, pineapple', 11.99);
INSERT INTO Pizza (PizzaID, Name, Specification, Price)
VALUES (5, 'Meat Feast', 'Tomato, mozzarella, assorted meats', 12.99);

-- Create Payment Table
CREATE TABLE Payment (
    PaymentID INT PRIMARY KEY,
    PDate DATE,
    Type VARCHAR(50),
    OrderID INT,
    CustomerID INT,
    Total DECIMAL(10, 2),
    FOREIGN KEY (OrderID) REFERENCES OrderHeader(OrderID),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

create or replace PROCEDURE data_transfer_1 (
    fromTable   IN VARCHAR2
    ,toTable    IN VARCHAR2   
) AS
    v_count NUMBER(6);
BEGIN

insert into Table2
select * from Table1;

END;

