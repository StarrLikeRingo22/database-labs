/*
TITLE: DBS211 - NEE PROJECT (GROUP)
DATE : 04/12/2022
MEMBERS:
1) Abdalla Abdelgadir (ID. 113734198)
2) Mohammed Mohammed (ID. 149244220)
3) Toluwani Aina (ID. 1008322370)
4) Madeline Bresil
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <cstring>

struct Account {
    int accountNumber;
    int customerID;
    double amount;
};


using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Function prototypes
void clearInputBuffer();
int findCustomerbyAccountNumber(Connection* conn, int customerID, struct Account* acc); // done
void addCustomer(Connection* conn, struct Account* acc); // done
void removeCustomer(Connection* conn, struct Account* acc); // eh
void updateCustomer(Connection* conn); // eh
void depositMoney(Connection* conn, struct Account* acc);  // wh
void displayCustomerDetails(Connection* conn, int customerID); // eh
void withdrawMoney(Connection* conn, struct Account* acc);
void requestLoan(Connection* conn); 
void displayCustomerDetailsByID(Connection* conn, int customerID);

void clearInputBuffer() {
    // Discard all remaining characters from the standard input buffer:
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// To pull ifnromation from SQL Table
int findCustomerbyAccountNumber(Connection* conn, int customerID, struct Account* acc) {
    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM Account WHERE account_number = " + to_string(customerID));

    if (rs->next()) {

        acc->accountNumber = rs->getInt(1);
        acc->customerID = rs->getInt(2);
        acc->amount = rs->getDouble(3);

        cout << "Customer found:" << endl;
        cout << "Account Number: " << rs->getInt(1) << endl;
        cout << "ID: " << rs->getInt(2) << endl;
        cout << "Balance : " << rs->getDouble(3) << endl;
        conn->terminateStatement(stmt);
        return 1;
        // Output other customer details
    }
    else {
        cout << "Customer not found." << endl;
        return 0;
    }

    conn->terminateStatement(stmt);
    return 1;
}
// BUSINESS OPERATION #1
void displayCustomerDetails(Connection* conn, int customerID) {
    Account acc;

    if (findCustomerbyAccountNumber(conn, customerID, &acc)) {
        cout << "Customer Details:" << endl;
        cout << "Account Number: " << acc.accountNumber << endl;
        cout << "Customer ID: " << acc.customerID << endl;
        cout << "Balance: " << acc.amount << endl;
    }
    else {
        cout << "Customer with ID " << customerID << " not found." << endl;
    }
    clearInputBuffer();
}


// BUSINESS OPERATION #2
// Function to add a new customer
void addCustomer(Connection* conn, struct Account* acc) {
    Statement* stmt = conn->createStatement();

    try {
        // Prompt user for customer's account number, customer ID, and balance
        cout << "Enter customer's account number: ";
        cin >> acc->accountNumber;
        cout << "Enter customer ID: ";
        cin >> acc->customerID;
        cout << "Enter balance: ";
        cin >> acc->amount;

        // Add a new account
        Statement* stmt = conn->createStatement("INSERT INTO Account (account_number, customer_id, balance) VALUES (:1, :2, :3)");
        stmt->setInt(1, acc->accountNumber);
        stmt->setInt(2, acc->customerID);
        stmt->setDouble(3, acc->amount);
        stmt->executeUpdate();
        conn->commit();
        cout << "New account added successfully. Customer ID: " << acc->customerID << endl;

        // Clean up
        conn->terminateStatement(stmt);
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}



//BUSINESS OPERATION #3
//function to remove customer
void removeCustomer(Connection* conn, struct Account* acc) {
    Statement* stmt = conn->createStatement();
    // Prompt user to remove their account
    char removeChoice;
    cout << "Do you want to remove your account? (y/n): ";
    cin >> removeChoice;

    if (removeChoice == 'y' || removeChoice == 'Y') {
        int inputCustomerId;
        cout << "Enter your 9-digit customer ID: ";
        cin >> inputCustomerId;

        // Find the account number for the given customer ID
        int accountNumber = findCustomerbyAccountNumber(conn, inputCustomerId, acc);

        if (acc->accountNumber != -1) {
            try {
                // Remove the account if input customer ID matches
                Statement* stmt = conn->createStatement("DELETE FROM Account WHERE account_number = :1");
                stmt->setInt(1, acc->accountNumber);
                int rowCount = stmt->executeUpdate();
                if (rowCount > 0) {
                    conn->commit();
                    cout << "Your account has been removed successfully." << endl;
                }
                else {
                    cout << "Invalid account number. Account removal failed." << endl;
                }

                // Clean up
                conn->terminateStatement(stmt);
            }
            catch (SQLException& ex) {
                cerr << "Error: " << ex.what() << endl;
            }
        }
        else {
            cout << "No account found for customer ID " << inputCustomerId << endl;
        }
    }
    else {
        cout << "Account removal canceled." << endl;
    }
    clearInputBuffer();
}


// BUSINESS OPERATION #4
// Function to update customer details
void updateCustomer(Connection* conn) {
    Account accountNumber;
    try {
        // Prompt user for customer ID
        int customerId;
        cout << "Enter Customer ID: ";
        cin >> customerId;

        // Find customer account number
        int success = findCustomerbyAccountNumber(conn, customerId, &accountNumber);

        // Display customer details
        displayCustomerDetails(conn, customerId);

        // Prompt user for which part to update
        cout << "Which part would you like to update? (name/address/phone number): ";
        string partToUpdate;
        cin >> partToUpdate;

        // Update customer details based on user input
        if (partToUpdate == "name") {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            Statement* stmt = conn->createStatement();
            int rowCount = stmt->executeUpdate("UPDATE Customer SET name = '" + newName + "' WHERE customer_id = " + to_string(customerId));
            conn->terminateStatement(stmt);
            if (rowCount > 0) {
                cout << "Customer name updated successfully." << endl;
            }
            else {
                cout << "Failed to update customer name." << endl;
            }
        }
        else if (partToUpdate == "address") {
            string newAddress;
            cout << "Enter new address: ";
            cin >> newAddress;
            Statement* stmt = conn->createStatement();
            int rowCount = stmt->executeUpdate("UPDATE Customer SET address = '" + newAddress + "' WHERE customer_id = " + to_string(customerId));
            conn->terminateStatement(stmt);
            if (rowCount > 0) {
                cout << "Customer address updated successfully." << endl;
            }
            else {
                cout << "Failed to update customer address." << endl;
            }
        }
        else if (partToUpdate == "phone number") {
            string newPhoneNumber;
            cout << "Enter new phone number: ";
            cin >> newPhoneNumber;
            Statement* stmt = conn->createStatement();
            int rowCount = stmt->executeUpdate("UPDATE Customer SET phone_number = '" + newPhoneNumber + "' WHERE customer_id = " + to_string(customerId));
            conn->terminateStatement(stmt);
            if (rowCount > 0) {
                cout << "Customer phone number updated successfully." << endl;
            }
            else {
                cout << "Failed to update customer phone number." << endl;
            }
        }
        else {
            cout << "Invalid input. No changes made." << endl;
        }
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
    clearInputBuffer();
}

//BUSINESS OPERATION #5
void viewTransactionHistory(Connection* conn, int accountNumber) {
    try {
        // Create a statement
        Statement* stmt = conn->createStatement();

        // Execute the query to retrieve transaction history
        string sqlQuery = "SELECT transaction_id, amount, transaction_type, transaction_date FROM Transaction WHERE account_number = :1";
        stmt->setInt(1, accountNumber);
        ResultSet* rs = stmt->executeQuery(sqlQuery);

        // Display the transaction history
        cout << "Transaction History for Account Number " << accountNumber << ":" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Transaction ID\tAmount\tType\tDate" << endl;
        while (rs->next()) {
            int transactionId = rs->getInt(1);
            double amount = rs->getDouble(2);
            string transactionType = rs->getString(3);
            string transactionDate = rs->getString(4);

            cout << transactionId << "\t\t" << amount << "\t" << transactionType << "\t" << transactionDate << endl;
        }

        // Clean up
        conn->terminateStatement(stmt);
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}

//BUSINESS OPERATION #6
// Function to deposit money into an account
void depositMoney(Connection* conn, struct Account* acc) {
    Statement* stmt = conn->createStatement();

    try {
        // Prompt user for account number and deposit amount
        cout << "Enter account number: ";
        cin >> acc->accountNumber;
        cout << "Enter amount to deposit: ";
        cin >> acc->amount;

        // Check if the account exists
        string sqlQuery = "SELECT customer_id FROM Account WHERE account_number = :1";
        stmt->setInt(1, acc->accountNumber);
        ResultSet* rs = stmt->executeQuery(sqlQuery);

        if (rs->next()) {
            // Retrieve customer ID
            acc->customerID = rs->getInt(2);

            // Update the account balance
            stmt = conn->createStatement("UPDATE Account SET balance = balance + :1 WHERE account_number = :2");
            stmt->setDouble(3, acc->amount);
            stmt->setInt(1, acc->accountNumber);
            stmt->executeUpdate();
            conn->commit();
            cout << "Deposit successful. New balance: " << acc->amount << endl;
        }
        else {
            cout << "Account not found. Deposit failed." << endl;
        }

        // Clean up
        conn->terminateStatement(stmt);
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

}

// BUSINESS OPERATION #7

void withdrawMoney(Connection* conn, struct Account* acc) {
    try {
        // Prompt user for account number
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;

        // Check if the account exists
        Statement* stmt = conn->createStatement();
        string sqlQuery = "SELECT balance FROM Account WHERE account_number = :1";
        stmt->setInt(1, accountNumber);
        ResultSet* rs = stmt->executeQuery(sqlQuery);

        if (rs->next()) {
            // Get current balance
            double balance = rs->getDouble(1);

            // Prompt user for withdrawal amount
            double amount;
            cout << "Enter amount to withdraw: ";
            cin >> amount;

            // Check if there's sufficient balance
            if (balance >= amount) {
                // Update the account balance
                double newBalance = balance - amount;
                stmt = conn->createStatement("UPDATE Account SET balance = :1 WHERE account_number = :2");
                stmt->setDouble(1, newBalance);
                stmt->setInt(2, accountNumber);
                stmt->executeUpdate();
                conn->commit();
                cout << "Withdrawal successful. New balance: " << newBalance << endl;
            }
            else {
                cout << "Insufficient balance. Withdrawal failed." << endl;
            }
        }
        else {
            cout << "Account not found. Withdrawal failed." << endl;
        }

        // Clean up
        conn->terminateStatement(stmt);
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}
// BUSINESS OPERATION #8
void requestLoan(Connection* conn) {
    try {
        int customerID;
        double income;

        // Prompt user for customer ID and income
        cout << "Enter your customer ID: ";
        cin >> customerID;

        cout << "Enter your current income: $";
        cin >> income;

        if (income < 50000) {
            cout << "Congratulations! Your loan request is approved." << endl;
            cout << "Please contact our nearest branch for further details." << endl;

            // You may add code here to update the loan status in the database
        }
        else {
            cout << "Sorry, your current income is above $50,000. You are not eligible for a loan." << endl;
        }
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}
//BUSINESS OPERATION #9
void displayCustomerDetailsByID(Connection* conn, int customerID) {
    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM CUSTOMER WHERE customer_id = " + to_string(customerID));

    if (rs->next()) {
        cout << "Customer Details:" << endl;
        cout << "Customer ID: " << rs->getInt(1) << endl;
        cout << "Name: " << rs->getString(2) << endl;
        cout << "Address: " << rs->getString(3) << endl;
        cout << "Phone Number: " << rs->getString(4) << endl;
    }
    else {
        cout << "Customer with ID " << customerID << " not found." << endl;
    }

    conn->terminateStatement(stmt);
}

//BUSINESS OPERATION #10
void openSavingsAccount(Connection* conn) {
    try {
        Account acc;
        int customerID;
        double transferAmount;

        // Prompt user for customer ID
        cout << "Enter your customer ID: ";
        cin >> customerID;

        // Prompt user for the amount to transfer
        cout << "Enter the amount of money to transfer: $";
        cin >> transferAmount;

        findCustomerbyAccountNumber(conn, customerID, &acc);

            // Add the new savings account
           Statement* stmt = conn->createStatement("INSERT INTO Account (customer_id, balance) VALUES (:1, :2)");
        stmt->setInt(1, customerID);
        stmt->setDouble(2, transferAmount);
        stmt->executeUpdate();
        conn->commit();
        cout << "Savings account opened successfully for Customer ID: " << customerID << endl;
    }
    catch (SQLException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}

int main(void) {
        /* OCCI Variables */
        Environment* env = nullptr;
    Connection* conn = nullptr;
    Statement* stmt = nullptr;

    /* Used Variables */
    string user = "dbs211_241nee01";
    string pass = "42911047";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(user, pass, constr);
        cout << "Connection is Successful!" << endl;
        // Menu loop
        while (true) {
            cout << "\nCustomer Management System\n";
            cout << "1) Display Customer Details \n";
            cout << "2) Add a Customer\n";
            cout << "3) Remove a Customer\n";
            cout << "4) Update a Customer\n";
            cout << "5) View Transaction History\n";
            cout << "6) Deposit Money\n";
            cout << "7) Withdraw Money\n";
            cout << "8) Request a Loan\n";
            cout << "9) Display Customer Details by ID\n";
            cout << "10) Open a Savings Account\n";
            cout << "11) Exit\n";
            cout << "Enter your choice: ";

            Account newAccount;
            Account acc;
            Account customerAccount;
            int choice;
            int numEntry = 0;
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Please Enter Account Number: ";
                cin >> numEntry;
                displayCustomerDetails(conn, numEntry);
                break;
            case 2:
                addCustomer(conn, &newAccount);
                break;
            case 3:
                removeCustomer(conn, &customerAccount);
                break;
            case 4:
                updateCustomer(conn);
                break;
            case 5:
                break;
            case 6:
                depositMoney(conn, &acc);
                break;
            case 7:
                withdrawMoney(conn, &acc);
                break;
            case 8:
                requestLoan(conn);
                break;
            case 9:
                cout << "Please Enter Customer ID: ";
                cin >> numEntry;
                displayCustomerDetailsByID(conn, numEntry);
                break;
            case 10:
                openSavingsAccount(conn);
                break;
            case 11:
                cout << "Exiting...";
                env->terminateConnection(conn);
                Environment::terminateEnvironment(env);
                return 0;
            default:
                cout << "Invalid choice. Please try again.";
            }
        }
    }
    catch (SQLException& sqlExcp) {
        cout << "Error code: " << sqlExcp.getErrorCode() << endl;
        cout << "Error message: " << sqlExcp.getMessage() << endl;
    }
}