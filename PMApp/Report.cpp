#include "Report.h"
#include "autofillFuncs.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Report::Report(sql::Connection* con, int newProjectID, const std::string& newOtherInformation) {
    if (newProjectID <= 0) {
        std::cout << "Project ID must be greater than 0." << std::endl;
        return;
    }
    this->otherInformation = newOtherInformation;
    this->projectID = newProjectID;

    int managerIDValue = fillManagerIdFromDatabase(con, newProjectID);
    int completedTasks = fillCompletedTasksFromDatabase(con, newProjectID);

    this->managerID = managerIDValue;
    this->numberOfCompletedTasks = completedTasks;

    
}

int fillManagerIdFromDatabase(sql::Connection* con, int projectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;
    int managerID = -1;

    try {
        pstmt = con->prepareStatement("SELECT manager_id FROM project_manager_assignments WHERE project_id = ?");
        pstmt->setInt(1, projectID);
        res = pstmt->executeQuery();

        if (res->next()) {
            managerID = res->getInt("manager_id");
        }
        else {
            std::cout << "Manager for project with ID " << projectID << " not found in the database." << std::endl;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQLException: " << e.what() << std::endl;
    }

    return managerID;
}

int fillCompletedTasksFromDatabase(sql::Connection* con, int projectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;
    int numberOfCompletedTasks = 0;

    try {
        pstmt = con->prepareStatement("SELECT COUNT(*) AS completed_tasks FROM tasks WHERE project_id = ? AND (status = 'completed' OR status = 'Completed')");
        pstmt->setInt(1, projectID);
        res = pstmt->executeQuery();

        if (res->next()) {
            numberOfCompletedTasks = res->getInt("completed_tasks");
        }
        else {
            std::cout << "No completed tasks found for project with ID " << projectID << "." << std::endl;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQLException: " << e.what() << std::endl;
    }

    return numberOfCompletedTasks;
}

void Report::insertDataToDatabase(sql::Connection* con)
{
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
};
std::string getReportByProjectID(sql::Connection* con, int wantedProjectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select report data by ID
        pstmt = con->prepareStatement("SELECT reports.*, projects.name FROM reports JOIN projects ON reports.project_id = projects.ID WHERE project_id = ?");
        pstmt->setInt(1, wantedProjectID);
        res = pstmt->executeQuery();

        std::string reportData = "";

        // Loop through the result set
        while (res->next()) {
            // Retrieving report data from the result set
            int ID = res->getInt("ID");
            int projectID = res->getInt("project_id");
            int managerID = res->getInt("manager_id");
            std::string projectName = res->getString("name");
            int numberOfCompletedTasks = res->getInt("number_of_completed_tasks");
            std::string otherInformation = res->getString("other_information");
            std::string reportDate = res->getString("report_date");

            // Formatting report data and appending to the string
            reportData += "===========\n";
            reportData += "Report no.: " + std::to_string(ID) + "\n";
            reportData += "Project ID: " + std::to_string(projectID) + "\n";
            reportData += "Project Name: " + projectName + "\n";
            reportData += "Manager ID: " + std::to_string(managerID) + "\n";
            reportData += "Number of Completed Tasks: " + std::to_string(numberOfCompletedTasks) + "\n";
            reportData += "Other Informations: " + otherInformation + "\n";
            reportData += "Report creation date: " + reportDate + "\n===========\n\n";
        }

        // Check if any records were found
        if (reportData.empty()) {
            reportData = "Report with project ID " + std::to_string(wantedProjectID) + " not found.";
        }

        delete res; // Clean up result set
        delete pstmt; // Clean up prepared statement

        return reportData;

    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        exit(1);
    }
};
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
};
