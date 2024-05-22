#include "database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <stdlib.h>

// =========================
// ---- DB CONNECTION ----
// =========================

// Database connection parameters
const std::string server = "tcp://127.0.0.1:3306";
const std::string username = "root";
const std::string password = "ZAQ!2wsx";

// Establishes connection to the database
sql::Connection* connectToDatabase() {
    sql::Driver* driver;
    sql::Connection* con;

    try {
        // Creating a driver instance to establish the connection
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // Setting the schema (database) to work with
        con->setSchema("pm_db");

        return con;
    }
    catch (sql::SQLException e) {
        // Handling connection errors
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

// =========================
// ---- INSERT DATA ----
// =========================

// Inserts data for a project manager into the database
void insertDataToProjectManagers(sql::Connection* con, const std::string& firstName, const std::string& lastName) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert project manager data
        pstmt = con->prepareStatement("INSERT INTO project_managers(first_name, last_name) VALUES(?,?)");
        pstmt->setString(1, firstName);
        pstmt->setString(2, lastName);
        pstmt->execute();
        std::cout << "Project manager inserted." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to project managers. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

// Funkcja powinna znaleźć się w pliku ProjectManager.h
// Inserts project manager assignment data into the database
void insertDataToProjectManagerAssignments(sql::Connection* con, int projectID, int managerID) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert project manager assignment data
        pstmt = con->prepareStatement("INSERT INTO project_manager_assignments(project_id, manager_id) VALUES(?,?)");
        pstmt->setInt(1, projectID);
        pstmt->setInt(2, managerID);
        pstmt->execute();
        std::cout << "Project manager assignment inserted." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to project manager assignments. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

// Inserts report data into the database
void insertDataToReports(sql::Connection* con, int projectID, int managerID, int numberOfCompletedTasks, const std::string& otherInformation) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert report data
        pstmt = con->prepareStatement("INSERT INTO reports(project_id, manager_id, number_of_completed_tasks, other_information) VALUES(?,?,?,?)");
        pstmt->setInt(1, projectID);
        pstmt->setInt(2, managerID);
        pstmt->setInt(3, numberOfCompletedTasks);
        pstmt->setString(4, otherInformation);
        pstmt->execute();
        std::cout << "Report inserted." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to reports. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

// =========================
// ---- GET DATA ----
// =========================

// Retrieves project manager data from the database based on manager ID
std::string getProjectManagerByID(sql::Connection* con, int managerID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select project manager data by ID
        pstmt = con->prepareStatement("SELECT * FROM project_managers WHERE ID = ?");
        pstmt->setInt(1, managerID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieving project manager data from the result set
            std::string firstName = res->getString("first_name");
            std::string lastName = res->getString("last_name");

            // Formatting project manager data into a string
            std::string managerData = "Project Manager ID: " + std::to_string(managerID) + "\n";
            managerData += "First Name: " + firstName + "\n";
            managerData += "Last Name: " + lastName + "\n";

            return managerData;
        }
        else {
            return "Project Manager with ID " + std::to_string(managerID) + " not found.";
        }

        delete res; // Clean up result set
        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        exit(1);
    }
}

// Retrieves report data from the database based on report ID
std::string getReportByID(sql::Connection* con, int reportID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select report data by ID
        pstmt = con->prepareStatement("SELECT * FROM reports WHERE ID = ?");
        pstmt->setInt(1, reportID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieving report data from the result set
            int projectID = res->getInt("project_id");
            int managerID = res->getInt("manager_id");
            int numberOfCompletedTasks = res->getInt("number_of_completed_tasks");
            std::string otherInformation = res->getString("other_information");

            // Formatting report data into a string
            std::string reportData = "Report ID: " + std::to_string(reportID) + "\n";
            reportData += "Project ID: " + std::to_string(projectID) + "\n";
            reportData += "Manager ID: " + std::to_string(managerID) + "\n";
            reportData += "Number of Completed Tasks: " + std::to_string(numberOfCompletedTasks) + "\n";
            reportData += "Other Information: " + otherInformation + "\n";

            return reportData;
        }
        else {
            return "Report with ID " + std::to_string(reportID) + " not found.";
        }

        delete res; // Clean up result set
        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        exit(1);
    }
}

// Funkcja powinna znaleźć się w pliku ProjectManager.h
void displayProjectsByManagerID(sql::Connection* con, int managerID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Prepare SQL query to retrieve projects assigned to a manager with the given ID
        pstmt = con->prepareStatement("SELECT p.* FROM projects p INNER JOIN project_manager_assignments a ON p.ID = a.project_id WHERE a.manager_id = ?");
        pstmt->setInt(1, managerID);
        res = pstmt->executeQuery();

        // Loop through the query results
        while (res->next()) {
            int projectID = res->getInt("ID");
            std::string name = res->getString("name");
            std::string description = res->getString("description");
            std::string startDate = res->getString("start_date");
            std::string endDate = res->getString("end_date");
            std::string status = res->getString("status");

            // Display project data
            std::cout << "Project ID: " << projectID << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Description: " << description << std::endl;
            std::cout << "Start Date: " << startDate << std::endl;
            std::cout << "End Date: " << endDate << std::endl;
            std::cout << "Status: " << status << std::endl;
            std::cout << std::endl;
        }

        // Free resources
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException e) {
        // Handle SQL exceptions
        std::cout << "SQL Exception: " << e.what() << std::endl;
        exit(1);
    }
}


// =========================
// ---- UPDATE DATA ----
// =========================

// Updates the number of completed tasks for a report in the database
void updateReportCompletedTasks(sql::Connection* con, int reportID, int numberOfCompletedTasks) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to update the number of completed tasks for a report
        pstmt = con->prepareStatement("UPDATE reports SET number_of_completed_tasks = ? WHERE ID = ?");
        pstmt->setInt(1, numberOfCompletedTasks);
        pstmt->setInt(2, reportID);
        pstmt->executeUpdate();
        std::cout << "Number of completed tasks updated for report ID: " << reportID << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not update number of completed tasks for report. Error message: " << e.what() << std::endl;
        exit(1);
    }
}
