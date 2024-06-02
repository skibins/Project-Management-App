#include "Employee.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


Employee::Employee(const std::string& employeeName, const std::string& employeelastName, const std::string& employeeposition) {
    if (employeeName.empty() || employeelastName.empty() || employeeposition.empty()) {
        std::cout << "All employee fields must be provided." << std::endl;
        return;
    }
    this->firstName = employeeName;
    this->lastName = employeelastName;
    this->position = employeeposition;
}

void Employee::insertDataToDatabase(sql::Connection* con) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert employee data
        pstmt = con->prepareStatement("INSERT INTO employees(first_name, last_name, position) VALUES(?,?,?)");
        pstmt->setString(1, firstName);
        pstmt->setString(2, lastName);
        pstmt->setString(3, position);
        pstmt->execute();
        std::cout << "Employee inserted." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to employees. Error message: " << e.what() << std::endl;
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
    }
}

std::string getEmployeeByID(sql::Connection* con, int employeeID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select employee data by ID
        pstmt = con->prepareStatement("SELECT * FROM employees WHERE ID = ?");
        pstmt->setInt(1, employeeID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieving employee data from the result set
            std::string firstName = res->getString("first_name");
            std::string lastName = res->getString("last_name");
            std::string position = res->getString("position");

            // Formatting employee data into a string
            std::string employeeData = "Employee ID: " + std::to_string(employeeID) + "\n";
            employeeData += "First Name: " + firstName + "\n";
            employeeData += "Last Name: " + lastName + "\n";
            employeeData += "Position: " + position + "\n";

            return employeeData;
        }
        else {
            return "Employee with ID " + std::to_string(employeeID) + " not found.";
        }

        delete res; // Clean up result set
        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
    }
}

void displayTasksByEmployeeID(sql::Connection* con, int employeeID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Prepare SQL query to retrieve tasks assigned to an employee with the given ID
        pstmt = con->prepareStatement("SELECT t.* FROM tasks t INNER JOIN assigned_tasks a ON t.ID = a.task_id WHERE a.employee_id = ?");
        pstmt->setInt(1, employeeID);
        res = pstmt->executeQuery();

        // Loop through the query results
        while (res->next()) {
            int taskID = res->getInt("ID");
            std::string name = res->getString("name");
            std::string description = res->getString("description");
            std::string priority = res->getString("priority");
            std::string startDate = res->getString("start_date");
            std::string endDate = res->getString("end_date");
            std::string status = res->getString("status");
            int projectID = res->getInt("project_id");

            // Display task data
            std::cout << "Task ID: " << taskID << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Description: " << description << std::endl;
            std::cout << "Priority: " << priority << std::endl;
            std::cout << "Start Date: " << startDate << std::endl;
            std::cout << "End Date: " << endDate << std::endl;
            std::cout << "Status: " << status << std::endl;
            std::cout << "Project ID: " << projectID << std::endl;
            std::cout << std::endl;
        }

        // Free resources
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException e) {
        // Handle SQL exceptions
        std::cout << "SQL Exception: " << e.what() << std::endl;
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
    }
}
