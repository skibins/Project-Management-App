#include "Menu.h"
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
            getline(cin, project_status);
            cout << "Enter updated project status: ";
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
            cout << getTaskByID(con, task_id);
            new_object = 0;
            break;
        case 4:
            cout << "Enter task's id: ";
            cin >> task_id;
            getline(cin, task_status);
            cout << "Enter updated task's status: ";
            getline(cin, task_status);
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
            cout << "Enter employee's name: ";
            getline(cin, employee_name);
            cout << "Enter employee's surname: ";
            getline(cin, employee_surname);
            cout << "Enter employee's position: ";
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

        string manager_name, manager_surname;
        int choice, new_object, manager_id, project_id;
        cin >> choice;

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
            cout << "Enter manager's id: ";
            cin >> manager_id;
            cout << getProjectManagerByID(con, manager_id);
            new_object = 0;
            break;
        case 3:
            cout << "Enter project's id: ";
            cin >> project_id;
            cout << "Enter manager's id: ";
            cin >> manager_id;
            insertDataToProjectManagerAssignments(con, project_id, manager_id);
            new_object = 0;
            break;
        case 4:
            cout << "Enter manager's id: ";
            cin >> manager_id;
            displayProjectsByManagerID(con, manager_id);
            new_object = 0;
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
        cout << "Schedules Menu:" << endl;
        cout << "1. Add new schedule" << endl;
        cout << "2. Show schedule by project ID" << endl;
        cout << "3. Update schedule's actual end date" << endl;
        cout << "4. Back to main menu" << endl;

        int choice, new_object, project_id, schedule_id;
        string schedule_date_end;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter project's id: ";
            cin >> project_id;
            getline(cin, schedule_date_end);
            cout << "Enter schedule's end date: ";
            getline(cin, schedule_date_end);
            new_object = 1;
            break;
        case 2:
            cout << "Enter project's id: ";
            cin >> project_id;
            cout << getScheduleByProjectID(con, project_id);
            new_object = 0;
            break;
        case 3:
            cout << "Enter schedule's id: ";
            cin >> schedule_id;
            cout << "Enter schedule date end: ";
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
        cout << "Reports Menu:" << endl;
        cout << "1. Add new report" << endl;
        cout << "2. Show report by project ID" << endl;
        cout << "3. Update report's completed tasks" << endl;
        cout << "4. Back to main menu" << endl;

        int choice, new_object, project_id, report_id, report_no_completed_tasks;
        string report_other_info;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter project's id: ";
            cin >> project_id;
            getline(cin, report_other_info);
            cout << "Enter report's other info: ";
            getline(cin, report_other_info);
            new_object = 1;
            break;
        case 2:
            cout << "Enter project's id: ";
            cin >> project_id;
            cout << getReportByProjectID(con, project_id);
            new_object = 0;
            break;
        case 3:
            cout << "Enter report's id: ";
            cin >> report_id;
            cout << "Enter report's number of completed tasks: ";
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