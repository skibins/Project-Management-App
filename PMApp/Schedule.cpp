#include "Schedule.h"
#include "autofillFuncs.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Schedule::Schedule(sql::Connection* con, int ScheduleProjectID, const std::string& ScheduleActualEndDate) {
    if (ScheduleProjectID <= 0 || ScheduleActualEndDate.empty()) {
        std::cout << "All fields must be provided, project ID must be greater than 0." << std::endl;
        return;
    }
    this->projectID = ScheduleProjectID;
    this->actualEndDate = ScheduleActualEndDate;

    std::string plannedEndDateValue = fillPlannedEndDateFromDatabase(con, ScheduleProjectID);
    this->plannedEndDate = plannedEndDateValue;
}

std::string fillPlannedEndDateFromDatabase(sql::Connection* con, int ScheduleProjectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        pstmt = con->prepareStatement("SELECT end_date FROM projects WHERE ID = ?");
        pstmt->setInt(1, ScheduleProjectID);
        res = pstmt->executeQuery();

        if (res->next()) {
            std::string plannedEndDate = res->getString("end_date");
            return plannedEndDate;
        }
        else {
            std::cout << "Project with ID " << ScheduleProjectID << " not found in the database." << std::endl;
            return "";
        }
    }
    catch (sql::SQLException& e) {
        std::cout << "SQLException: " << e.what() << std::endl;
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
        return "";
    }

    delete res;
    delete pstmt;
}


void Schedule::insertDataToDatabase(sql::Connection* con)
{
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
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
    }
	
}

std::string getScheduleByProjectID(sql::Connection* con, int wantedProjectID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to select schedule data by ID
        pstmt = con->prepareStatement("SELECT schedules.*, projects.name FROM schedules JOIN projects ON schedules.project_id = projects.ID WHERE schedules.project_id = ? ;");
        pstmt->setInt(1, wantedProjectID);
        res = pstmt->executeQuery();

        std::string scheduleData = "";  // Initialize an empty string to store data

        // Loop through the result set
        while (res->next()) {
            // Retrieving schedule data from the result set
            int ID = res->getInt("ID");
            int projectID = res->getInt("project_id");
            std::string projectName = res->getString("name");
            std::string plannedEndDate = res->getString("planned_end_date");
            std::string actualEndDate = res->getString("actual_end_date");

            // Formatting schedule data and appending to the string
            scheduleData += "===========\n";
            scheduleData += "Schedule no.: " + std::to_string(ID) + "\n";
            scheduleData += "Project ID: " + std::to_string(projectID) + "\n";
            scheduleData += "Project Name: " + projectName + "\n";
            scheduleData += "Planned End Date: " + plannedEndDate + "\n";
            scheduleData += "Actual End Date: " + actualEndDate + "\n===========\n\n";
        }

        // Check if any records were found
        if (scheduleData.empty()) {
            scheduleData = "Schedule with project ID " + std::to_string(wantedProjectID) + " not found.";
        }

        delete res; // Clean up result set
        delete pstmt; // Clean up prepared statement

        return scheduleData;

    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
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
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
    }
}
