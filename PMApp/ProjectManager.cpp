#include "ProjectManager.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

ProjectManager::ProjectManager(const std::string& newFirstName, const std::string& newLastName) : firstName(newFirstName), lastName(newLastName) {};

void ProjectManager::insertDataToDatabase(sql::Connection* con) {
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
};

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
};

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
};

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
};