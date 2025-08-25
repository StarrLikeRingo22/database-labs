-- ***********************
-- Name: Abdalla Abdelgadir, Mohammed Mohammed, Toluwani Aina, Madeline Bresil
-- ID: 113734198, 149244220, 1008322370
-- Date: 04/12/2024
-- Purpose: Group Project DBS211
-- ***********************

CREATE TABLE Customer (
    customer_id INT PRIMARY KEY,
    name VARCHAR(255),
    ssn VARCHAR(11) UNIQUE,
    address VARCHAR(255),
    phone_number VARCHAR(15)
);
CREATE TABLE Account (
    account_number INT PRIMARY KEY,
    customer_id INT,
    balance DECIMAL(10, 2),
    FOREIGN KEY (customer_id) REFERENCES Customer(customer_id)
);
CREATE TABLE Transaction (
    transaction_id INT PRIMARY KEY,
    account_number INT,
    amount DECIMAL(10, 2),
    transaction_type VARCHAR2(20),
    transaction_date TIMESTAMP,
    FOREIGN KEY (account_number) REFERENCES Account(account_number),
    CONSTRAINT chk_transaction_type CHECK (transaction_type IN ('deposit', 'withdrawal', 'transfer'))
);
CREATE TABLE Branch (
    branch_id INT PRIMARY KEY,
    name VARCHAR(255),
    location VARCHAR(255)
);
CREATE TABLE Employee (
    employee_id INT PRIMARY KEY,
    name VARCHAR(255),
    position VARCHAR(255),
    branch_id INT,
    FOREIGN KEY (branch_id) REFERENCES Branch(branch_id)
);