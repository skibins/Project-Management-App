#include <iostream>
#include "string.h"
#include "database.h"
#include "Project.h"
#include "Task.h"
#include "Employee.h"
#include "Schedule.h"
#include "ProjectManager.h"
#include "Report.h"
#include "regex"

using namespace std;

bool isValidDate(const string& date) {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

void projectsMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Projects Menu:" << endl;
        cout << "1. Add new project" << endl;
        cout << "2. Show all projects" << endl;
        cout << "3. Show project" << endl;
        cout << "4. Update project status" << endl;
        cout << "5. Back to main menu" << endl;

        int choice, project_id, new_object;
        string project_name, project_desc, project_date_start, project_date_end, project_status;

        cin >> choice;

        switch (choice) {
        case 1:
            getline(cin, project_name);
            cout << "Enter project name: ";
            getline(cin, project_name);
            cout << "Enter project descripton: ";
            getline(cin, project_desc);
            while (true) {
                cout << "Enter project start date: ";
                getline(cin, project_date_start);
                if (isValidDate(project_date_start)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            while (true) {
                cout << "Enter project end date: ";
                getline(cin, project_date_end);
                if (isValidDate(project_date_end)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            cout << "Enter project status: ";
            getline(cin, project_status);
            //cout << "Project name: " << project_name << " project description: " << project_name << " project start date: " << project_date_start << " projest end date: " << project_date_end << " project status:  " << project_status<<"\n";
            new_object = 1;
            break;
        case 2:
            cout << getAllProjects(con);
            new_object = 0;
            break;
        case 3:
            cout << "Enter projects id: ";
            cin >> project_id;
            cout << getProjectByID(con, project_id);
            new_object = 0;
            break;
        case 4:
            cout << "Enter projects id: ";
            cin >> project_id;
            cout << "Enter updated project status: ";
            cin >> project_status;
            updateProjectStatus(con, project_id, project_status);
            new_object = 0;
            break;
        case 5:
            new_object = 0;
            return;
        default:
            new_object = 0;
            cout << "Invalid option, try again." << endl;
        }
        if (new_object = 1) {
            Project project(project_name, project_desc, project_date_start, project_date_end, project_status);
            project.insertDataToDatabase(con);
        }

    }
}

void tasksMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Tasks Menu:" << endl;
        cout << "1. Add new task" << endl;
        cout << "2. Show all tasks" << endl;
        cout << "3. Show task" << endl;
        cout << "4. Update task status" << endl;
        cout << "5. Assign task to an employee" << endl;
        cout << "6. Back to main menu" << endl;

        int choice, task_id, employee_id, new_object;
        string task_name, task_desc, task_prio, task_date_start, task_date_end, task_status;
        cin >> choice;

        switch (choice) {
        case 1:
            getline(cin, task_name);
            cout << "Enter task's name: ";
            getline(cin, task_name);
            cout << "Enter task's descripton: ";
            getline(cin, task_desc);
            cout << "Enter task's priority: ";
            getline(cin, task_prio);
            while (true) {
                cout << "Enter task's start date: ";
                getline(cin, task_date_start);
                if (isValidDate(task_date_start)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            while (true) {
                cout << "Enter task's end date: ";
                getline(cin, task_date_end);
                if (isValidDate(task_date_end)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            cout << "Enter task's status: ";
            getline(cin, task_status);
            cout << "Enter project's id: ";
            cin >> task_id;
            new_object = 1;
            break;
        case 2:
            cout << getAllTasks(con);
            new_object = 0;
            break;
        case 3:
            cout << "Enter task's id: ";
            cin >> task_id;
            cout << getTaskByID (con, task_id);
            new_object = 0;
            break;
        case 4:
            cout << "Enter task's id: ";
            cin >> task_id;
            cout << "Enter updated task's status: ";
            cin >> task_status;
            updateTaskStatus(con, task_id, task_status);
            new_object = 0;
            break;
        case 5:
            cout << "Enter task's id: ";
            cin >> task_id;
            cout << "Enter employee's id: ";
            cin >> employee_id;
            insertDataToAssignedTasks(con, task_id, employee_id);
            new_object = 0;
            break;
        case 6:
            new_object = 0;
            return;
        default:
            new_object = 0;
            cout << "Invalid option, try again." << endl;
        }
        if (new_object == 1) {
            Task task(task_name, task_desc, task_prio, task_date_start, task_date_end, task_status, task_id);
            task.insertDataToDatabase(con);
        }
    }
}

void employeesMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Employees Menu:" << endl;
        cout << "1. Add new employee" << endl;
        cout << "2. Show employee" << endl;
        cout << "3. Display employee's tasks" << endl;
        cout << "4. Back to main menu" << endl;

        int choice, employee_id, new_object;
        string employee_name, employee_surname, employee_position;
        cin >> choice;

        switch (choice) {
        case 1:
            getline(cin, employee_name);
            cout << "Enter project name: ";
            getline(cin, employee_surname);
            cout << "Enter project descripton: ";
            getline(cin, employee_position);
            new_object = 1;
            break;
        case 2:
            cout << "Enter employee's id: ";
            cin >> employee_id;
            cout << getEmployeeByID(con, employee_id);
            new_object = 0;
            break;
        case 3:
            cout << "Enter employee's id: ";
            cin >> employee_id;
            displayTasksByEmployeeID(con, employee_id);
            new_object = 0;
            break;
        case 4:
            new_object = 0;
            return;
        default:
            new_object = 0;
            cout << "Invalid option, try again." << endl;
        }
        if (new_object == 1) {
            Employee employee(employee_name, employee_surname, employee_position);
            employee.insertDataToDatabase(con);
        }
    }
}

void projectManagersMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Project Managers Menu:" << endl;
        cout << "1. Add new manager" << endl;
        cout << "2. Show manager" << endl;
        cout << "3. Assign project to a manager" << endl;
        cout << "4. Display manager's projects" << endl;
        cout << "5. Back to main menu" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        default:
            cout << "Invalid option, try again." << endl;
        }
    }
}

void schedulesMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Schedules Menu:" << endl;
        cout << "1. Add new schedule" << endl;
        cout << "2. Show schedule by project ID" << endl;
        cout << "3. Update schedule's actual end date" << endl;
        cout << "4. Back to main menu" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        default:
            cout << "Invalid option, try again." << endl;
        }
    }
}

void reportsMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {
        cout << "Reports Menu:" << endl;
        cout << "1. Add new report" << endl;
        cout << "2. Show report by project ID" << endl;
        cout << "3. Update report's completed tasks" << endl;
        cout << "4. Back to main menu" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        default:
            cout << "Invalid option, try again." << endl;
        }
    }
}

int main() {
    // Establish connection to the database
    sql::Connection* con = connectToDatabase();

    // =========================
    // - VARIABLES DECLARATION -
    // =========================

    int option;

    // =========================
    // ------- MAIN MENU -------
    // =========================

    while (true) {
        cout << "MAIN MENU" << endl;
        cout<<endl;

        cout << "Choose an option:" << endl;
        cout << "1. Projects" << endl;
        cout << "2. Tasks" << endl;
        cout << "3. Employees" << endl;
        cout << "4. Project Managers" << endl;
        cout << "5. Schedules" << endl;
        cout << "6. Reports" << endl;
        cout << "7. Exit" << endl;
        
        cout << ":";
        cin >> option;
        switch (option) {
        case 1:
            projectsMenu();
            break;
        case 2:
            tasksMenu();
            break;
        case 3:
            employeesMenu();
            break;
        case 4:
            projectManagersMenu();
            break;
        case 5:
            schedulesMenu();
            break;
        case 6:
            reportsMenu();
            break;
        case 7:
            exit(0);
        default:
            cout << "Invalid option, try again." << endl;
        }

    }

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
