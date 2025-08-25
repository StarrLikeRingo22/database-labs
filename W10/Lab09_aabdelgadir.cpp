#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

void insertData(Connection* conn) {
    Statement* stmt = conn->createStatement();
    ResultSet* rs = stmt->executeQuery("SELECT MAX(ID) FROM Customer"); // Get the maximum ID
    int maxID = 0;
    if (rs->next()) {
        maxID = rs->getInt(1);
    }
    stmt->closeResultSet(rs);

    int newID = maxID++; 
    string name = "New Entry";

    stmt = conn->createStatement("INSERT INTO Customer (CustomerID, FName) VALUES (:1, :2)");
    stmt->setInt(1, newID); // Set value for the first parameter
    stmt->setString(2, name); // Set value for the second parameter
    stmt->executeUpdate(); // Execute the SQL INSERT statement
    conn->commit(); // Commit the transaction
    cout << "Data inserted successfully with ID: " << newID << endl;
    stmt->closeResultSet(rs);
    conn->terminateStatement(stmt);
}

bool placeOrder(Connection* conn, int customerID, int pizzaID, int quantity, string deliveryType) {
    try {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN PlaceOrder(:1, :2, :3, :4, sysdate); END;"); 
        stmt->setInt(1, customerID);
        stmt->setInt(2, pizzaID);
        stmt->setInt(3, quantity);
        stmt->setString(4, deliveryType);
        stmt->executeUpdate();
        conn->commit();
        conn->terminateStatement(stmt);
        return true;
    }
    catch (SQLException& ex) {
        cout << "Error occurred: " << ex.what() << endl;
        return false;
    }
}

bool transferDataSp(Connection* conn) {
    Statement* stmt = conn->createStatement();
    stmt->setSQL("BEGIN data_transfer_1(:1, :2); END;");
    stmt->setString(1, "Table1");
    stmt->setString(2, "Table2");

    //stmt->executeUpdate(); 
    stmt->executeQuery();
}


int main() {

    /* OCCI Variables */
    Environment* env = nullptr;
    Connection* conn = nullptr;
    Statement* stmt = nullptr; 

    /* Used Variables */
    string user = "dbs211_241nee01";
    string pass = "42911047";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

    /* Create a connection */
    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(user, pass, constr);

    /* Task 2.2
   
    insertData(conn);
    */

    /* Task 3.1 
    transferDataSp(conn);
    */
    /* Task 3.2
    int customerID = 1;
    int pizzaID = 1;
    int quantity = 2;
    string deliveryType = "Home Delivery";
    if (placeOrder(conn, customerID, pizzaID, quantity, deliveryType)) {
        cout << "Order placed successfully." << endl;
    }
    else {
        cout << "Failed to place the order." << endl;
    } */

    // Cleanup
    conn->terminateStatement(stmt);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return 0;
}