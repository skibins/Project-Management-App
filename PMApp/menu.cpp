#include "Menu.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
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

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Projects Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new project" << endl; Sleep(50);
        cout << "| 2 | Show all projects" << endl; Sleep(50);
        cout << "| 3 | Show project" << endl; Sleep(50);
        cout << "| 4 | Update project status" << endl; Sleep(50);
        cout << "| 5 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);

        int choice, project_id, new_object;
        string project_name, project_desc, project_date_start, project_date_end, project_status;

        cin >> choice;

        system("cls");

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
            cout << "Enter project status (Completed / In Progress / Planned): ";
            getline(cin, project_status);
            new_object = 1;
            break;
        case 2:
            cout << getAllProjects(con);
            new_object = 0;
            system("pause");
            break;
        case 3:
            cout << "Enter projects id: ";
            cin >> project_id;
            cout << getProjectByID(con, project_id);
            new_object = 0;
            system("pause");
            break;
        case 4:
            cout << "Enter projects id: ";
            cin >> project_id;
            getline(cin, project_status);
            cout << "Enter updated project status (Completed / In progress / Planned): ";
            getline(cin, project_status);
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
        if (new_object == 1) {
            Project project(project_name, project_desc, project_date_start, project_date_end, project_status);
            project.insertDataToDatabase(con);
        }

    }
}

void tasksMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Tasks Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new task" << endl; Sleep(50);
        cout << "| 2 | Show all tasks" << endl; Sleep(50);
        cout << "| 3 | Show task" << endl; Sleep(50);
        cout << "| 4 | Update task status" << endl; Sleep(50);
        cout << "| 5 | Assign task to an employee" << endl; Sleep(50);
        cout << "| 6 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl;

        int choice, task_id, employee_id, new_object;
        string task_name, task_desc, task_prio, task_date_start, task_date_end, task_status;
        cin >> choice;

        system("cls");

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
                cout << "Enter task's start date (yyyy-mm-dd): ";
                getline(cin, task_date_start);
                if (isValidDate(task_date_start)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            while (true) {
                cout << "Enter task's end date (yyyy-mm-dd): ";
                getline(cin, task_date_end);
                if (isValidDate(task_date_end)) {
                    break;
                }
                else {
                    cout << "Bad date format (yyyy-mm-dd), try again!\n";
                }
            }
            cout << "Enter task's status (Completed / In progress / Planned): ";
            getline(cin, task_status);
            cout << "Enter project's id (must be an integer): ";
            cin >> task_id;
            new_object = 1;
            break;
        case 2:
            cout << getAllTasks(con);
            new_object = 0;
            system("pause");
            break;
        case 3:
            // Showing a specific task
            cout << "Enter task's id (must be an integer): ";
            cin >> task_id;
            cout << getTaskByID(con, task_id);
            new_object = 0;
            system("pause");
            break;
        case 4:
            // Updating task status
            cout << "Enter task's id (must be an integer): ";
            cin >> task_id;
            getline(cin, task_status);
            cout << "Enter updated task's status (Completed / In Progress / Planned): ";
            getline(cin, task_status);
            updateTaskStatus(con, task_id, task_status);
            new_object = 0;
            break;
        case 5:
            // Assigning a task to an employee
            cout << "Enter task's id (must be an integer): ";
            cin >> task_id;
            cout << "Enter employee's id (must be an integer): ";
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

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Employees Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new employee" << endl; Sleep(50);
        cout << "| 2 | Show employee" << endl; Sleep(50);
        cout << "| 3 | Display employee's tasks" << endl; Sleep(50);
        cout << "| 4 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);

        int choice, employee_id, new_object;
        string employee_name, employee_surname, employee_position;
        cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            getline(cin, employee_name);
            cout << "Enter employee's name: ";
            getline(cin, employee_name);
            cout << "Enter employee's surname: ";
            getline(cin, employee_surname);
            cout << "Enter employee's position: ";
            getline(cin, employee_position);
            new_object = 1;
            break;
        case 2:
            // Showing a specific employee
            cout << "Enter employee's id (must be an integer): ";
            cin >> employee_id;
            cout << getEmployeeByID(con, employee_id);
            new_object = 0;
            system("pause");
            break;
        case 3:
            // Displaying tasks assigned to an employee
            cout << "Enter employee's id (must be an integer): ";
            cin >> employee_id;
            displayTasksByEmployeeID(con, employee_id);
            new_object = 0;
            system("pause");
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

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Project Managers Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new manager" << endl; Sleep(50);
        cout << "| 2 | Show manager" << endl; Sleep(50);
        cout << "| 3 | Assign project to a manager" << endl; Sleep(50);
        cout << "| 4 | Display manager's projects" << endl; Sleep(50);
        cout << "| 5 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; 

        string manager_name, manager_surname;
        int choice, new_object, manager_id, project_id;
        cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            getline(cin, manager_name);
            cout << "Enter manager's name: ";
            getline(cin, manager_name);
            cout << "Enter manager's surname: ";
            getline(cin, manager_surname);
            new_object = 1;
            break;
        case 2:
            // Showing a specific manager
            cout << "Enter manager's id (must be an integer): ";
            cin >> manager_id;
            cout << getProjectManagerByID(con, manager_id);
            new_object = 0;
            system("pause");
            break;
        case 3:
            // Assigning a project to a manager
            cout << "Enter project's id (must be an integer): ";
            cin >> project_id;
            cout << "Enter manager's id (must be an integer): ";
            cin >> manager_id;
            insertDataToProjectManagerAssignments(con, project_id, manager_id);
            new_object = 0;
            break;
        case 4:
            // Displaying projects assigned to a manager
            cout << "Enter manager's id (must be an integer): ";
            cin >> manager_id;
            displayProjectsByManagerID(con, manager_id);
            new_object = 0;
            system("pause");
            break;
        case 5:
            new_object = 0;
            return;
        default:
            cout << "Invalid option, try again." << endl;
        }
        if (new_object == 1) {
            ProjectManager projectManager(manager_name, manager_surname);
            projectManager.insertDataToDatabase(con);
        }
    }
}

void schedulesMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Schedules Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new schedule" << endl; Sleep(50);
        cout << "| 2 | Show schedule by project ID" << endl; Sleep(50);
        cout << "| 3 | Update schedule's actual end date" << endl; Sleep(50);
        cout << "| 4 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl;

        int choice, new_object, project_id, schedule_id;
        string schedule_date_end;
        cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            // Adding a new schedule
            cout << "Enter project's id (must be an integer): ";
            cin >> project_id;
            getline(cin, schedule_date_end);
            cout << "Enter schedule's end date (yyy-mm-dd): ";
            getline(cin, schedule_date_end);
            new_object = 1;
            break;
        case 2:
            // Showing schedule by project ID
            cout << "Enter project's id (must be an integer): ";
            cin >> project_id;
            cout << getScheduleByProjectID(con, project_id);
            new_object = 0;
            system("pause");
            break;
        case 3:
            // Updating schedule's actual end date
            cout << "Enter schedule's id (must be an integer): ";
            cin >> schedule_id;
            cout << "Enter schedule date end (yyyy-mm-dd): ";
            cin >> schedule_date_end;
            updateScheduleActualEndDate(con, schedule_id, schedule_date_end);
            new_object = 0;
            break;
        case 4:
            new_object = 0;
            return;
        default:
            cout << "Invalid option, try again." << endl;
        }
        if (new_object == 1) {
            Schedule schedule(con, project_id, schedule_date_end);
            schedule.insertDataToDatabase(con);
        }
    }
}

void reportsMenu() {
    sql::Connection* con = connectToDatabase();
    while (true) {

        system("cls");

        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Reports Menu:" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Add new report" << endl; Sleep(50);
        cout << "| 2 | Show report by project ID" << endl; Sleep(50);
        cout << "| 3 | Update report's completed tasks" << endl; Sleep(50);
        cout << "| 4 | Back to main menu" << endl; Sleep(50);
        cout << "|------------------------------------" << endl;

        int choice, new_object, project_id, report_id, report_no_completed_tasks;
        string report_other_info;
        cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            // Adding a new report
            cout << "Enter project's id (must be an integer): ";
            cin >> project_id;
            getline(cin, report_other_info);
            cout << "Enter report's other info: ";
            getline(cin, report_other_info);
            new_object = 1;
            break;
        case 2:
            // Showing report by project ID
            cout << "Enter project's id (must be an integer): ";
            cin >> project_id;
            cout << getReportByProjectID(con, project_id);
            new_object = 0;
            system("pause");
            break;
        case 3:
            // Updating report's completed tasks
            cout << "Enter report's id (must be an integer): ";
            cin >> report_id;
            cout << "Enter report's number of completed tasks (must be an integer): ";
            cin >> report_no_completed_tasks;
            updateReportCompletedTasks(con, report_id, report_no_completed_tasks);
            new_object = 0;
            break;
        case 4:
            new_object = 0;
            return;
        default:
            cout << "Invalid option, try again." << endl;
        }
        if (new_object == 1) {
            Report report(con, project_id, report_other_info);
            report.insertDataToDatabase(con);
        }
    }
}

void showupScreen() { 

    srand(time(NULL));

    cout << "\n\n\n\n\n\n\n\n\n\n\n                                                     Loading . . ." << endl << endl;

    cout << "                                                  ";

    for (int i = 0; i < 20; i++) {
        int random = rand() %200+50;
        cout << "|";
        Sleep(random);
    }
    system("cls");



    string submit;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 13);

    // App title screen
    setlocale(LC_ALL, "");
    cout << endl;
    cout << "  XXXXX   XXXXX    XXXX   XXXXXX  XXXXX    XXXXX  XXXXXX                                                                " << endl;    Sleep(100);
    cout << "  XX  XX  XX  XX  XX  XX      XX  XX      XX        XX                                                                  " << endl;    Sleep(100);
    cout << "  XXXXX   XXXXX   XX  XX      XX  XXXXX   XX        XX                                                                  " << endl;    Sleep(100);
    cout << "  XX      XX XX   XX  XX  XX  XX  XX      XX        XX                                                                  " << endl;    Sleep(100);
    cout << "  XX      XX  XX   XXXX    XXXX   XXXXX    XXXXX    XX                                                                  " << endl;    Sleep(100);
    cout << endl;                                                                                                                                  Sleep(100);
    cout << "  XX   XX   XXXX   XX   XX   XXXX    XXXXX   XXXXX  XX   XX  XXXXX  XX   XX  XXXXXX        XXXX   XXXXX   XXXXX         " << endl;    Sleep(100);
    cout << "  XXX XXX  XX  XX  XXX  XX  XX  XX  XX       XX     XXX XXX  XX     XXX  XX    XX         XX  XX  XX  XX  XX  XX        " << endl;    Sleep(100);
    cout << "  XX X XX  XXXXXX  XX X XX  XXXXXX  XX  XXX  XXXXX  XX X XX  XXXXX  XX X XX    XX         XXXXXX  XXXXX   XXXXX         " << endl;    Sleep(100);
    cout << "  XX   XX  XX  XX  XX  XXX  XX  XX  XX   XX  XX     XX   XX  XX     XX  XXX    XX         XX  XX  XX      XX            " << endl;    Sleep(100);
    cout << "  XX   XX  XX  XX  XX   XX  XX  XX   XXXXX   XXXXX  XX   XX  XXXXX  XX   XX    XX         XX  XX  XX      XX            " << endl;    Sleep(100);
    cout << endl;

    SetConsoleTextAttribute(hConsole, 4);

    cout << "X     X    X      XXX                                                                                              " << endl;    Sleep(100);
    cout << " X   X     X     X   X                                                                                             " << endl;    Sleep(100);
    cout << "  X X      X     X   X                                                                                             " << endl;    Sleep(100);
    cout << "   X       X  X   XXX                                                                                              " << endl;    Sleep(100);

    Sleep(300);

    SetConsoleTextAttribute(hConsole, 14);

    cout << endl << "                                                                                           Created by:          " << endl;    Sleep(50);
    cout << "                                                                                               Jan Skibiñski            " << endl;    Sleep(50);
    cout << "                                                                                               Micha³ Bujok             " << endl;    Sleep(50);
    cout << "                                                                                               Sebastian Paszek         " << endl;    Sleep(150);
    cout << endl;

    SetConsoleTextAttribute(hConsole, 4);

    cout << "                                     press RETURN to continue" << endl;

    SetConsoleTextAttribute(hConsole, 2);

    cout << "                                           ";
    getline(cin, submit);
    system("cls");
}