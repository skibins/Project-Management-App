#include <iostream>
#include "database.h"
#include "Project.h"
#include "Task.h"

using namespace std;

int main() {
    // Establish connection to the database
    sql::Connection* con = connectToDatabase();

    // =========================
    // ---- READY CLASSES ----
    // =========================

    // Project class usage example

    Project project("Sample Project", "This is a sample project description.", "2024-04-30", "2024-05-30", "In Progress");


    //project.insertDataToDatabase(con);

    cout << getProjectByID(con, 2) << endl;

    //updateProjectStatus(con, 2, "another test status");

    // Task class usage example

    Task task("Nazwa zadania", "Opis zadania", "Wysoki", "2024-04-30", "", "In progress", 2);

    //task.insertDataToDatabase(con);

    cout << getTaskByID(con, 2) << endl;

    //insertDataToAssignedTasks(con, 3, 1);

    //updateTaskStatus(con, 2, "another Test status");

    // =========================
    // ---- INSERT DATA ----
    // =========================

    /*
    // Inserting data for an employee
    insertDataToEmployees(con, "Janek", "Ski", "Developer");
    
    // Inserting data for a project manager
    insertDataToProjectManagers(con, "Carol", "Johnson");

    // Assigning the project manager to a project
    insertDataToProjectManagerAssignments(con, 2, 3);

    // Inserting report data
    insertDataToReports(con, 1, 1, 2, "Additional information for project 1");

    // Inserting schedule data
    insertDataToSchedules(con, 2, "2024-08-31", "");
    */

    // =========================
    // ---- UPDATE DATA ----
    // =========================

    /*
    // Updating the actual end date of the schedule
    updateScheduleActualEndDate(con, 1, "2024-08-15");

    // Updating the number of completed tasks in the report
    updateReportCompletedTasks(con, 1, 5);

    // Updating the status of the project
    updateProjectStatus(con, 1, "Completed");
    */

    // =========================
    // ---- SHOW DATA ----
    // =========================

    /*
    // Retrieving and printing employee data
    string employeeData = getEmployeeByID(con, 1);
    cout << "Employee Data:\n" << employeeData << endl;

    // Retrieving and printing project manager data
    string managerData = getProjectManagerByID(con, 1);
    cout << "Project Manager Data:\n" << managerData << endl;

    // Retrieving and printing report data
    string reportData = getReportByID(con, 1);
    cout << "Report Data:\n" << reportData << endl;

    // Retrieving and printing schedule data
    string scheduleData = getScheduleByID(con, 1);
    cout << "Schedule Data:\n" << scheduleData << endl;

    // Displaying tasks assigned to the employee.
    cout << "Tasks attached to employee 1:" << endl;
    displayTasksByEmployeeID(con, 1);

    // Displaying projects assigned to the manager.
    cout << "Projects attached to manager 1:" << endl;
    displayProjectsByManagerID(con, 1);
    */

    // Closing the database connection
    delete con;

    return 0;
}
