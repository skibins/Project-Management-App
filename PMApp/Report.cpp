#include "Report.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Report::Report(int newProjectID, int newManagerID, int newNumberOfCompletedTask, const std::string& newOtherInformation) : numberOfCompletedTasks(newNumberOfCompletedTask), otherInformation(newOtherInformation), projectID(newProjectID), managerID(newManagerID) {}

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
