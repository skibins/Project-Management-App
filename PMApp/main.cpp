#include <iostream>
#include "database.h"
#include "Project.h"
#include "Task.h"
#include "Employee.h"
#include "Schedule.h"
#include "ProjectManager.h"
#include "Report.h"

using namespace std;

int main() {
    // Establish connection to the database
    sql::Connection* con = connectToDatabase();

    // =========================
    // ---- READY CLASSES ----
    // =========================
    
    // ProjectManager uasage example

    //ProjectManager projectManager("John", "test");

    //projectManager.insertDataToDatabase(con);

    //insertDataToProjectManagerAssignments(con, 1, 1);
    
    //cout << getProjectManagerByID(con, 2);

    //displayProjectsByManagerID(con, 2);

    // =========================

    // Project class usage example

    //Project project("Sample Project", "Desc", "2024-04-30", "2024-05-30", "In Progress");

    //project.insertDataToDatabase(con);

    //cout << getProjectByID(con, 2) << endl;

    //cout << getAllProjects(con) << endl;

    //updateProjectStatus(con, 2, "another test status");

    // =========================

    // Task class usage example
    
    //Task task("Nazwa zadania", "Opis zadania", "Wysoki", "2024-04-30", "", "In progress", 2);

    //task.insertDataToDatabase(con);

    //cout << getTaskByID(con, 2) << endl;

    //cout << getAllTasks(con) << endl;

    //insertDataToAssignedTasks(con, 3, 1);

    //updateTaskStatus(con, 2, "another Test status");

    // =========================

    // Employee class usage example
    
    //Employee employee("Jan", "Nazwisko", "pracownik");

    //employee.insertDataToDatabase(con);

    //displayTasksByEmployeeID(con, 2);

    //cout << getEmployeeByID(con, 2) << endl;

    // =========================

    // Schedule class usage example

    //Schedule schedule(con, 2, "2024-02-11");

    //schedule.insertDataToDatabase(con);

    //updateScheduleActualEndDate(con, 2, "2025-11-11");

    //cout << getScheduleByProjectID(con, 2) << endl;

    // =========================

    // Report class usage example

    //Report report1(con, 1, "test");

    //report1.insertDataToDatabase(con);

    //cout << getReportByProjectID(con, 1);

    //updateReportCompletedTasks(con, 1, 6);

    // =========================

    // Closing the database connection
    delete con;

    return 0;
}
