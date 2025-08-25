#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Question 1
void createTable(Connection* conn) {
    Statement* stmt = conn->createStatement("CREATE TABLE YourUserNameEmployees AS SELECT * FROM dbs211_employees WHERE 1=0");
    //    Statement* stmt = conn->createStatement("CREATE TABLE student AS SELECT * FROM dbs211_employees WHERE 1=0");
    stmt->executeUpdate();
    conn->terminateStatement(stmt);
}

//Question 2
void insertData(Connection* conn) {
    Statement* stmt = conn->createStatement("INSERT INTO YourUserNameEmployees (EMAIL, EMPLOYEENUMBER, EXTENSION, FIRSTNAME, LASTNAME, JOBTITLE, OFFICECODE, REPORTSTO) VALUES ('aabdelgadir@example.com', '113734198', '211', 'Abdalla', 'Abdelgadir', 'Developer', '1', NULL)");
    stmt->executeUpdate();
    conn->terminateStatement(stmt);
}

//Question 3
void showEmployeeInfo(Connection* conn) {
    Statement* stmt = conn->createStatement("SELECT * FROM YourUserNameEmployees");
    ResultSet* rs = stmt->executeQuery();

    while (rs->next()) {
        cout << "StudentNumber: " << rs->getInt(1) << endl;
        cout << "LastName: " << rs->getString(2) << endl;
        cout << "FirstName: " << rs->getString(3) << endl;
        cout << "Course Code: " << rs->getString(4) << endl;
        cout << "Email: " << rs->getString(5) << endl;
        cout << "OfficeCode: " << rs->getString(6) << endl;
    }

    conn->terminateStatement(stmt);
}

//Question 4
void updateJobTitle(Connection* conn) {
    Statement* stmt = conn->createStatement("UPDATE YourUserNameEmployees SET jobTitle = 'unknown'");
    stmt->executeUpdate();

    cout << "Job titles updated successfully!" << endl;

    conn->terminateStatement(stmt);
}

//Question 5
void deleteEmployees(Connection* conn) {
    Statement* stmt = conn->createStatement("DELETE FROM YourUserNameEmployees");
    stmt->executeUpdate();
    conn->terminateStatement(stmt);
}

//Question 6
void displayEmployeesInSanFrancisco(Connection* conn) {
    Statement* stmt = conn->createStatement("SELECT EMAIL, EMPLOYEENUMBER, FIRSTNAME, LASTNAME, EXTENSION FROM Dbs211_Employees WHERE OFFICECODE = '4' ORDER BY EMPLOYEENUMBER");
    ResultSet* rs = stmt->executeQuery();

    // Display column headers
    cout << "Employee Number  First Name  Last Name  Extension  Email" << endl;

    // Loop through the result set and display each row
    while (rs->next()) {
        cout << rs->getInt(2) << "  " << rs->getString(3) << "  " << rs->getString(4) << "  " << rs->getString(5) << "  " << rs->getString(1) << endl;
    }

    // Clean up resources
    conn->terminateStatement(stmt);
}
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

        //Question 1
        //createTable(conn);
        //cout << "Table created successfully!" << endl;
        
        //Question 2
        //insertData(conn);
        //cout << "Data inserted successfully!" << endl;

        //Question 3
        //showEmployeeInfo(conn);
        
        //Question 4
        //updateJobTitle(conn);
        //cout << "Job title updated!" << endl;
        
        //Question 5
        //deleteEmployees(conn);
        //cout << "Employees deleted successfully" << endl;

        //Question 6
        displayEmployeesInSanFrancisco(conn);

        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp) {
        cout << "Error code: " << sqlExcp.getErrorCode() << endl;
        cout << "Error message: " << sqlExcp.getMessage() << endl;
    }
    return 0;
}