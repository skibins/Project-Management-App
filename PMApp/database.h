#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cppconn/connection.h>

// =========================
// ---- DB CONNECTION ----
// =========================

// Establishes connection to the database
sql::Connection* connectToDatabase();

// =========================
// ---- INSERT DATA ----
// =========================

// Inserts data for an employee
void insertDataToEmployees(sql::Connection* con, const std::string& firstName, const std::string& lastName, const std::string& position);

// Inserts task data
void insertDataToTasks(sql::Connection* con, const std::string& name, const std::string& description, const std::string& priority, const std::string& startDate, const std::string& endDate, const std::string& status, int projectID);

// Inserts data for a project manager
void insertDataToProjectManagers(sql::Connection* con, const std::string& firstName, const std::string& lastName);

// Assigns a project manager to a project
void insertDataToProjectManagerAssignments(sql::Connection* con, int projectID, int managerID);

// Inserts report data
void insertDataToReports(sql::Connection* con, int projectID, int managerID, int numberOfCompletedTasks, const std::string& otherInformation);

// Inserts schedule data
void insertDataToSchedules(sql::Connection* con, int projectID, const std::string& plannedEndDate, const std::string& actualEndDate);

// Assigns a task to an employee
void insertDataToAssignedTasks(sql::Connection* con, int taskID, int employeeID);

// =========================
// ---- GET DATA ----
// =========================

// Retrieves task data by its ID
std::string getTaskByID(sql::Connection* con, int taskID);

// Retrieves employee data by their ID
std::string getEmployeeByID(sql::Connection* con, int employeeID);

// Retrieves project manager data by their ID
std::string getProjectManagerByID(sql::Connection* con, int managerID);

// Retrieves report data by its ID
std::string getReportByID(sql::Connection* con, int reportID);

// Retrieves schedule data by its ID
std::string getScheduleByID(sql::Connection* con, int scheduleID);

// Displays tasks attached to an employee by ID. 
void displayTasksByEmployeeID(sql::Connection* con, int employeeID);

// Displays projects attached to the manager by ID.
void displayProjectsByManagerID(sql::Connection* con, int managerID);

// =========================
// ---- UPDATE DATA ----
// =========================

// Updates the actual end date of the schedule
void updateScheduleActualEndDate(sql::Connection* con, int scheduleID, const std::string& actualEndDate);

// Updates the number of completed tasks in the report
void updateReportCompletedTasks(sql::Connection* con, int reportID, int numberOfCompletedTasks);

#endif
