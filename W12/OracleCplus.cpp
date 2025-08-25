#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <cstring>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Function prototypes
int findCustomerbyAccountNumber(Connection* conn, int customerID, struct Account* acc);
void findCustomerByName(Connection* conn);
void customerReport(Connection* conn);
void addCustomer(Connection* conn, struct Account* acc);
void removeCustomer(Connection* conn, struct Account* acc);
void updateCustomer(Connection* conn);
void depositMoney(Connection* conn, int accountNumber, double amount);
void displayCustomerDetails(Connection* conn, int customerID);
struct Account {
    int accountNumber;
    int customerID;
    double amount;
};

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

void findCustomerByName(Connection* conn) {
    string customerName;
    cout << "Enter Customer Name: ";
    cin.ignore(); // Ignore any previous newline character in the input buffer
    getline(cin, customerName); // Read the entire line, including spaces

    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM dbs211_customers WHERE customer_name = '" + customerName + "'");

    if (rs->next()) {
        cout << "Customer found:" << endl;
        cout << "ID: " << rs->getInt(1) << endl;
        cout << "Name: " << rs->getString(2) << endl;
        // Output other customer details
    }
    else {
        cout << "Customer not found." << endl;
    }

    conn->terminateStatement(stmt);
}


void customerReport(Connection* conn) {

    Statement* stmt = nullptr;
    // Account and branch IDs
    int accountID = 123; // Replace with the actual account ID
    int branchID = 456;  // Replace with the actual branch ID

    // Assign account to branch
        stmt = conn->createStatement("UPDATE Account SET branch_id = :1 WHERE account_id = :2");
        stmt->setInt(1, branchID);
        stmt->setInt(2, accountID);
        stmt->executeUpdate();
        conn->commit();
        cout << "Account assigned to branch successfully." << endl;
    conn->terminateStatement(stmt);
}

// Function to generate a random 9-digit number
int generateCustomerId() {
    return rand() % 900000000 + 100000000;
}
// Function to add a new customer
void addCustomer(Connection* conn, struct Account* acc) {
    Statement* stmt = conn->createStatement();

    try {
        // Prompt user for customer's account number, customer ID, and balance
        cout << "Enter customer's account number: ";
        cin >> acc->accountNumber;
        if (acc->accountNumber != 9) {
            cout << "Please enter a digit limited to 9 digits: ";
            cin >> acc->accountNumber;
        }

        cout << "Enter customer ID: ";
        cin >> acc->customerID;
        if (acc->customerID != 4) {
            cout << "Please enter a digit limited to 4 digits: ";
            cin >> acc->customerID;
        }
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

int findAccountNumber(Connection* conn, int customerId) {
    Statement* stmt = conn->createStatement();
    //ResultSet* rs = stmt->executeQuery("SELECT e1.employeenumber, e1.lastname, e1.firstname, e1.email, phone, e1.extension, e2.firstname || ' ' || e2.lastname AS reportsto, e1.jobtitle, city FROM employees e1 LEFT JOIN employees e2 ON e1.reportsto = e2.employeenumber JOIN offices ON e1.officecode = offices.officecode WHERE e1.employeenumber IS NOT NULL AND e1.employeenumber= " + to_string(employeeNumber));

    int accountNumber = -1; // Initialize to a default value

    // Prompt the user to enter the customer ID
    cout << "Enter the customer ID: ";
    cin >> accountNumber;

    // Find the account number for the given customer ID
    accountNumber = findAccountNumber(conn, accountNumber);

    // Display the result
    if (accountNumber != -1) {
        cout << "Account number for customer ID " << customerId << " is: " << accountNumber << endl;
    }
    else {
        cout << "No account found for customer ID " << customerId << endl;
    }

    // Clean up
    conn->terminateStatement(stmt);

    return EXIT_SUCCESS;
}


// Function to remove a customer
void removeCustomer(Connection* conn, struct Account* acc) {
    Statement* stmt = conn->createStatement();

    // Prompt user to remove their account
    char removeChoice;
    cout << "Do you want to remove your account? (y/n): ";
    cin >> removeChoice;

    if (removeChoice == 'y' || removeChoice == 'Y') {
        cout << "Enter your 4-digit account number: ";
        int customerID;
        cin >> customerID;

        if (findCustomerbyAccountNumber(conn, customerID, acc)) {
            try {
                // Remove the account if input account number ID matches
                stmt->setInt(2, customerID);

                int rowCount = stmt->executeUpdate("DELETE FROM Account WHERE customer_id = " + to_string(customerID));
                if (rowCount > 0) {
                    conn->commit();
                    cout << "Your account has been removed successfully." << endl;
                }
                else {
                    cout << "Invalid customer ID. Account removal failed." << endl;
                }

                // Clean up
                conn->terminateStatement(stmt);
            }
            catch (SQLException& ex) {
                cerr << "Error: " << ex.what() << endl;
            }
        }
        else {
            cout << "Customer with ID " << customerID << " does not exist." << endl;
        }
    }
}
    

void updateCustomer(Connection* conn) {
    int customerID;
    string newEmail; // Add other fields to update as needed
    cout << "Enter Customer ID: ";
    cin >> customerID;
    cout << "Enter New Email: ";
    cin >> newEmail;

    Statement* stmt = conn->createStatement();
    int rowCount = stmt->executeUpdate("UPDATE dbs211_customers SET customer_email = '" + newEmail + "' WHERE customer_id = " + to_string(customerID));

    if (rowCount > 0) {
        cout << "Customer updated successfully." << endl;
    }
    else {
        cout << "Failed to update customer." << endl;
    }
    conn->terminateStatement(stmt);
}

void depositMoney(Connection* conn, int accountNumber, double amount) {
    Statement* stmt = conn->createStatement();

    try {
        // Execute query to deposit money into the account
        stmt->setSQL("UPDATE Account SET balance = balance + :1 WHERE account_number = :2");
        stmt->setDouble(1, amount); // Assuming balance is stored as double in the database
        stmt->setInt(2, accountNumber);
        stmt->executeUpdate();

        std::cout << "Deposit of $" << amount << " into account number " << accountNumber << " successful." << std::endl;
    }
    catch (SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    conn->terminateStatement(stmt);
}


void displayCustomerDetails(Connection* conn, int customerID) {
    struct Account acc;

    if (findCustomerByID(conn, customerID, &acc)) {
        cout << "Customer Details:" << endl;
        cout << "Account Number: " << acc.accountNumber << endl;
        cout << "Customer ID: " << acc.customerID << endl;
        cout << "Balance: " << acc.amount << endl;
    }
    else {
        cout << "Customer with ID " << customerID << " not found." << endl;
    }
}
int main(void) {
    struct Account 
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
            cout << "1) Find a Customer by \n";
            cout << "2) Remove Customere\n";
            cout << "3) Customer Report\n";
            cout << "4) Add a Customer\n";
            cout << "5) Update a Customer\n";
            cout << "6) Deposit Money\n";
            cout << "7) Display Customer Details"
            cout << "8) Exit\n";
            cout << "Enter your choice: ";
            
            Account newAccount;
            Account acc;
            Account customerAccount;
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                int numEntry;
                cout << "Please Enter Account Number: ";
                cin >> numEntry
                findCustomerbyAccountNumber(conn, 0, &customerAccount);
                break;
            case 2:

                removeCustomer(conn, &acc);
                break;
            case 3:
                customerReport(conn);
                break;
            case 4:
                addCustomer(conn, &newAccount);
                break;
            case 5:
                updateCustomer(conn);
                break;
            case 6:
                depositMoney(conn, 11, 1234.24);
                break;
            case 7:
                displayCustomerDetails(conn, &acc);
                break;
            case 8:
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