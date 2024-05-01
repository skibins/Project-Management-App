#include "Task.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Task::Task(const std::string& taskName, const std::string& taskDescription, const std::string& taskPriority, const std::string& taskStartDate, const std::string& taskEndDate, const std::string& taskStatus, int taskProjectID)
    : name(taskName), description(taskDescription), priority(taskPriority), startDate(taskStartDate), endDate(taskEndDate), status(taskStatus), projectID(taskProjectID) {}

void Task::insertDataToDatabase(sql::Connection* con) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Preparing SQL statement to insert task data
        pstmt = con->prepareStatement("INSERT INTO tasks(name, description, priority, start_date, end_date, status, project_id) VALUES(?,?,?,?,?,?,?)");
        pstmt->setString(1, name);
        pstmt->setString(2, description);
        pstmt->setString(3, priority);
        pstmt->setString(4, startDate);
        pstmt->setString(5, endDate);
        pstmt->setString(6, status);
        pstmt->setInt(7, projectID);
        pstmt->execute();
        std::cout << "Task inserted to the database." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to tasks. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

std::string getTaskByID(sql::Connection* con, int taskID) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Prepare SQL statement to retrieve task data by ID
        pstmt = con->prepareStatement("SELECT * FROM tasks WHERE ID = ?");
        pstmt->setInt(1, taskID);
        res = pstmt->executeQuery();

        if (res->next()) {
            // Retrieve task data from the result set
            std::string name = res->getString("name");
            std::string description = res->getString("description");
            std::string priority = res->getString("priority");
            std::string startDate = res->getString("start_date");
            std::string endDate = res->getString("end_date");
            std::string status = res->getString("status");
            int projectID = res->getInt("project_id");

            // Format task data into a string
            std::string taskData = "Task ID: " + std::to_string(taskID) + "\n";
            taskData += "Name: " + name + "\n";
            taskData += "Description: " + description + "\n";
            taskData += "Priority: " + priority + "\n";
            taskData += "Start Date: " + startDate + "\n";
            taskData += "End Date: " + endDate + "\n";
            taskData += "Status: " + status + "\n";
            taskData += "Project ID: " + std::to_string(projectID) + "\n";

            return taskData;
        }
        else {
            return "Task with ID " + std::to_string(taskID) + " not found.";
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


void updateTaskStatus(sql::Connection* con, int taskID, const std::string& status) {
    sql::ResultSet* res = nullptr;
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Check if the task with the given ID exists in the database
        pstmt = con->prepareStatement("SELECT ID FROM tasks WHERE ID = ?");
        pstmt->setInt(1, taskID);
        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Cannot update status - task with the given ID does not exist." << std::endl;
            delete pstmt;
            delete res;
            return; // Exit the function if the task does not exist
        }

        // Update the task status
        delete pstmt; // Delete the existing prepared statement

        pstmt = con->prepareStatement("UPDATE tasks SET status = ? WHERE ID = ?");
        pstmt->setString(1, status);
        pstmt->setInt(2, taskID);
        pstmt->executeUpdate();
        std::cout << "Task status updated for task ID: " << taskID << std::endl;

        delete pstmt; // Delete the prepared statement
        delete res; // Delete the result set
    }
    catch (sql::SQLException e) {
        // Handle SQL errors
        std::cout << "SQL Exception: " << e.what() << std::endl;
        if (res) delete res; // Delete the result set in case of an error
        if (pstmt) delete pstmt; // Delete the prepared statement in case of an error
        exit(1);
    }
}

void insertDataToAssignedTasks(sql::Connection* con, int taskID, int employeeID) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // Prepare SQL statement to check if the task exists
        pstmt = con->prepareStatement("SELECT * FROM tasks WHERE ID = ?");
        pstmt->setInt(1, taskID);
        sql::ResultSet* res = pstmt->executeQuery();

        // If task does not exist, print message and return
        if (!res->next()) {
            std::cout << "Task with ID " << taskID << " does not exist." << std::endl;
            return;
        }

        // Prepare SQL statement to check if the employee exists
        pstmt = con->prepareStatement("SELECT * FROM employees WHERE ID = ?");
        pstmt->setInt(1, employeeID);
        res = pstmt->executeQuery();

        // If employee does not exist, print message and return
        if (!res->next()) {
            std::cout << "Employee with ID " << employeeID << " does not exist." << std::endl;
            return;
        }

        // Prepare SQL statement to insert assigned task data
        pstmt = con->prepareStatement("INSERT INTO assigned_tasks(task_id, employee_id) VALUES(?,?)");
        pstmt->setInt(1, taskID);
        pstmt->setInt(2, employeeID);
        pstmt->execute();
        std::cout << "Assignment of the task inserted to the database." << std::endl;

        delete pstmt; // Clean up prepared statement
    }
    catch (sql::SQLException e) {
        // Handling SQL errors
        std::cout << "Could not insert data to assigned tasks. Error message: " << e.what() << std::endl;
        exit(1);
    }
}