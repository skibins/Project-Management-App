#include "Schedule.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Schedule::Schedule(int ScheduleProjectID, const std::string& SchedulePlannedEndDate, const std::string& ScheduleActualEndDate)
    : projectID(ScheduleProjectID), plannedEndDate(SchedulePlannedEndDate), actualEndDate(ScheduleActualEndDate) {};

void insertDataToSchedules(sql::Connection* con, int projectID, const std::string& plannedEndDate, const std::string& actualEndDate) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert schedule data
        pstmt = con->prepareStatement("INSERT INTO schedules(project_id, planned_end_date, actual_end_date) VALUES(?,?,?)");
        pstmt->setInt(1, projectID);
        pstmt->setString(2, plannedEndDate);
        pstmt->setString(3, actualEndDate);
        pstmt->execute();
        std::cout << "Schedule inserted." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to schedules. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

std::string getScheduleByID(sql::Connection* con, int scheduleID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select schedule data by ID
        pstmt = con->prepareStatement("SELECT * FROM schedules WHERE ID = ?");
        pstmt->setInt(1, scheduleID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieving schedule data from the result set
            int projectID = res->getInt("project_id");
            std::string plannedEndDate = res->getString("planned_end_date");
            std::string actualEndDate = res->getString("actual_end_date");

            // Formatting schedule data into a string
            std::string scheduleData = "Schedule ID: " + std::to_string(scheduleID) + "\n";
            scheduleData += "Project ID: " + std::to_string(projectID) + "\n";
            scheduleData += "Planned End Date: " + plannedEndDate + "\n";
            scheduleData += "Actual End Date: " + actualEndDate + "\n";

            return scheduleData;
        }
        else {
            return "Schedule with ID " + std::to_string(scheduleID) + " not found.";
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

void updateScheduleActualEndDate(sql::Connection* con, int scheduleID, const std::string& actualEndDate) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to update actual end date for a schedule
        pstmt = con->prepareStatement("UPDATE schedules SET actual_end_date = ? WHERE ID = ?");
        pstmt->setString(1, actualEndDate);
        pstmt->setInt(2, scheduleID);
        pstmt->executeUpdate();
        std::cout << "Actual end date updated for schedule ID: " << scheduleID << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not update actual end date for schedule. Error message: " << e.what() << std::endl;
        exit(1);
    }
}
