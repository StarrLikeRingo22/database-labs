#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Task 3.2
int createTable(Connection* conn, string tablename, string createStmt) {

	// create the table
	try {
		Statement* stmt = conn->createStatement(createStmt);

		// store the returned data in a result set
		stmt->executeUpdate();
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		return false;
	}
	cout << "Table creation successful!" << endl;
	return true;
}

// Task 3.3
bool maxCreditHours(Connection* conn) {
	int maxCreditHours = 0;
	string maxCreditHoursSQL = "SELECT MAX(CreditHours) FROM courses";

	Statement* stmt = conn->createStatement(maxCreditHoursSQL);

	// Store the returned data in a result set
	ResultSet* rs = stmt->executeQuery();

	if (!rs->next()) {
		// If the result set is empty
		cout << "Data does not exist." << endl;
		return false;
	}
	else {
		maxCreditHours = rs->getInt(1);
		cout << "MAX CREDIT HOURS:" << maxCreditHours << endl;
	}
}

// Task 3.4
bool callMaximumDepartmentSalarySP(Connection* conn, int departmentId) {
	try {
		// Create a statement
		Statement* stmt = conn->createStatement();

		// Set the SQL statement with the stored procedure call
		stmt->setSQL("BEGIN maximum_department_salary(:1); END;");

		// Bind the department_id parameter
		stmt->setInt(1, departmentId);

		// Execute the statement
		stmt->executeUpdate();

		// Clean up
		conn->terminateStatement(stmt);

		return true; // Success
	}
	catch (SQLException& sqlExcp) {
		cout << "SQL error: " << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
		return false; // Failure
	}
	catch (exception& ex) {
		cout << "Exception occurred: " << ex.what() << endl;
		return false; // Failure
	}
}

// Task 3.5
bool deleteCourseWithMaxCreditHours(Connection* conn) {
	try {
		// Query to delete the course with the maximum credit hours
		string deleteSQL = "DELETE FROM courses WHERE CreditHours = (SELECT MAX(CreditHours) FROM courses)";

		// Execute the delete query
		Statement* stmt = conn->createStatement(deleteSQL);
		stmt->executeUpdate();

		// Clean up
		conn->terminateStatement(stmt);
		cout << "Course with maximum credit hours deleted successfully." << endl;
		return true;
	}
	catch (SQLException& sqlExcp) {
		cout << "SQL error: " << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
		return false;
	}
	catch (exception& ex) {
		cout << "Exception occurred: " << ex.what() << endl;
		return false;
	}
}

// Task 3.1
int main()
{
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;

	/* Used Variables */
	string user = "dbs211_241nee01";
	string pass = "42911047";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	// Establishes connection to oracle sql server
	conn = env->createConnection(user, pass, constr);
	cout << "Connection is Successful!" << endl;

	try {

		// Define the table name and create statement
		string tableToCreate = "courses";
		string tableCreateStatement = "CREATE TABLE courses (ID NUMBER NOT NULL, Name VARCHAR2(100) NOT NULL, CreditHours NUMBER(2))";

		// Call the createTable function
		int createStatus = createTable(conn, tableToCreate, tableCreateStatement);

		// Call maxCreditHours to find and delete the maximum credit hours
		//maxCreditHours(conn);
		//deleteCourseWithMaxCreditHours(conn);
		
		// Terminate connection and environment
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
		return 1;
	}
}
