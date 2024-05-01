#include "Project.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Project::Project(const std::string& projectName, const std::string& projectDescription, const std::string& projectStartDate, const std::string& projectEndDate, const std::string& projectStatus)
    : name(projectName), description(projectDescription), startDate(projectStartDate), endDate(projectEndDate), status(projectStatus) {}

void Project::insertDataToDatabase(sql::Connection* con) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert project data
        pstmt = con->prepareStatement("INSERT INTO projects(name, description, start_date, end_date, status) VALUES(?,?,?,?,?)");
        pstmt->setString(1, name);
        pstmt->setString(2, description);
        pstmt->setString(3, startDate);
        pstmt->setString(4, endDate);
        pstmt->setString(5, status);
        pstmt->execute();
        std::cout << "Project inserted to the database." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to projects. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

std::string getProjectByID(sql::Connection* con, int projectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select project data by ID
        pstmt = con->prepareStatement("SELECT * FROM projects WHERE ID = ?");
        pstmt->setInt(1, projectID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieving project data from the result set
            std::string name = res->getString("name");
            std::string description = res->getString("description");
            std::string startDate = res->getString("start_date");
            std::string endDate = res->getString("end_date");
            std::string status = res->getString("status");

            // Formatting project data into a string
            std::string projectData = "Project ID: " + std::to_string(projectID) + "\n";
            projectData += "Name: " + name + "\n";
            projectData += "Description: " + description + "\n";
            projectData += "Start Date: " + startDate + "\n";
            projectData += "End Date: " + endDate + "\n";
            projectData += "Status: " + status + "\n";

            return projectData;
        }
        else {
            return "Project with ID " + std::to_string(projectID) + " not found.";
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

void updateProjectStatus(sql::Connection* con, int projectID, const std::string& status) {
    sql::ResultSet* res = nullptr;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Check if the project with the given ID exists in the database
        pstmt = con->prepareStatement("SELECT ID FROM projects WHERE ID = ?");
        pstmt->setInt(1, projectID);
        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Cannot update status - project with the given ID does not exist." << std::endl;
            delete pstmt;
            delete res;
            return; // Exit the function if the project does not exist
        }

        // Update the project status
        delete pstmt; // Delete the existing prepared statement

        pstmt = con->prepareStatement("UPDATE projects SET status = ? WHERE ID = ?");
        pstmt->setString(1, status);
        pstmt->setInt(2, projectID);
        pstmt->executeUpdate();
        std::cout << "Status updated for project ID: " << projectID << std::endl;

        delete pstmt; // Delete the prepared statement
        delete res; // Delete the result set
    }
    catch (sql::SQLException e) {
        // Handle SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        if (res) delete res; // Delete the result set in case of an error
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
        exit(1);
    }
}
