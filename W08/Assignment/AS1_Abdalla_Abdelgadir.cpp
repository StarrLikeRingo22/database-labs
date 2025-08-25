#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Function prototypes
void findCustomerByID(Connection* conn);
void findCustomerByName(Connection* conn);
void customerReport(Connection* conn);
void addCustomer(Connection* conn);
void updateCustomer(Connection* conn);
void removeCustomer(Connection* conn);

int main(void) {
    /* OCCI Variables */
    Environment* env = nullptr;
    Connection* conn = nullptr;

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
            cout << "1) Find a Customer by ID\n";
            cout << "2) Find a Customer by Name\n";
            cout << "3) Customer Report\n";
            cout << "4) Add a Customer\n";
            cout << "5) Update a Customer\n";
            cout << "6) Remove a Customer\n";
            cout << "7) Exit\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                findCustomerByID(conn);
                break;
            case 2:
                findCustomerByName(conn);
                break;
            case 3:
                customerReport(conn);
                break;
            case 4:
                addCustomer(conn);
                break;
            case 5:
                updateCustomer(conn);
                break;
            case 6:
                removeCustomer(conn);
                break;
            case 7:
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

void findCustomerByID(Connection* conn) {
    int customerID;
    cout << "Enter Customer ID: ";
    cin >> customerID;

    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM customers WHERE customer_id = " + to_string(customerID));

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

void findCustomerByName(Connection* conn) {
    string customerName;
    cout << "Enter Customer Name: ";
    cin.ignore(); // Ignore any previous newline character in the input buffer
    getline(cin, customerName); // Read the entire line, including spaces

    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM customers WHERE customer_name = '" + customerName + "'");

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
    int customerID;
    cout << "Enter Customer ID: ";
    cin >> customerID;

    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT * FROM customers WHERE customer_id = " + to_string(customerID));

    if (rs->next()) {
        cout << "Customer Details:" << endl;
        cout << "ID: " << rs->getInt(1) << endl;
        cout << "Name: " << rs->getString(2) << endl;
        // Output other customer details

        // Query customer order information
        ResultSet* orderRS = stmt->executeQuery("SELECT * FROM orders WHERE customer_id = " + to_string(customerID));
        // Output order details

        // Query purchased product information
        ResultSet* productRS = stmt->executeQuery("SELECT * FROM products WHERE product_id IN "
            "(SELECT product_id FROM order_details WHERE order_id IN "
            "(SELECT order_id FROM orders WHERE customer_id = " + to_string(customerID) + "))");
        // Output product details

    }
    else {
        cout << "Customer not found." << endl;
    }

    conn->terminateStatement(stmt);
}


void addCustomer(Connection* conn) {
    string customerName, customerEmail; // Add other customer details as needed
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter Customer Email: ";
    getline(cin, customerEmail);

    Statement* stmt = conn->createStatement();
    int rowCount = stmt->executeUpdate("INSERT INTO customers (customer_name, customer_email) "
        "VALUES ('" + customerName + "', '" + customerEmail + "')");

    if (rowCount > 0) {
        cout << "Customer added successfully." << endl;
    }
    else {
        cout << "Failed to add customer." << endl;
    }

    conn->terminateStatement(stmt);
}
void updateCustomer(Connection* conn) {
    int customerID;
    string newEmail; // Add other fields to update as needed
    cout << "Enter Customer ID: ";
    cin >> customerID;
    cout << "Enter New Email: ";
    cin >> newEmail;

    Statement* stmt = conn->createStatement();
    int rowCount = stmt->executeUpdate("UPDATE customers SET customer_email = '" + newEmail + "' WHERE customer_id = " + to_string(customerID));

    if (rowCount > 0) {
        cout << "Customer updated successfully." << endl;
    }
    else {
        cout << "Failed to update customer." << endl;
    }

    conn->terminateStatement(stmt);
}

void removeCustomer(Connection* conn) {
    int customerID;
    cout << "Enter Customer ID: ";
    cin >> customerID;

    Statement* stmt = conn->createStatement();
    int rowCount = stmt->executeUpdate("DELETE FROM customers WHERE customer_id = " + to_string(customerID));

    if (rowCount > 0) {
        cout << "Customer removed successfully." << endl;
    }
    else {
        cout << "Failed to remove customer." << endl;
    }

    conn->terminateStatement(stmt);
}

