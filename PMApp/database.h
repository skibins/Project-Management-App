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

// Inserts data for a project manager
//void insertDataToProjectManagers(sql::Connection* con, const std::string& firstName, const std::string& lastName);

// Assigns a project manager to a project
//void insertDataToProjectManagerAssignments(sql::Connection* con, int projectID, int managerID);

// Inserts report data
void insertDataToReports(sql::Connection* con, int projectID, int managerID, int numberOfCompletedTasks, const std::string& otherInformation);

// =========================
// ---- GET DATA ----
// =========================

// Retrieves project manager data by their ID
//std::string getProjectManagerByID(sql::Connection* con, int managerID);

// Retrieves report data by its ID
std::string getReportByID(sql::Connection* con, int reportID);

// Displays projects attached to the manager by ID.
//void displayProjectsByManagerID(sql::Connection* con, int managerID);

// =========================
// ---- UPDATE DATA ----
// =========================

// Updates the number of completed tasks in the report
void updateReportCompletedTasks(sql::Connection* con, int reportID, int numberOfCompletedTasks);

#endif
