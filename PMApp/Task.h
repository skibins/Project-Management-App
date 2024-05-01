#pragma once

#include <string>
#include <mysql_connection.h>

std::string getTaskByID(sql::Connection* con, int taskID);
void updateTaskStatus(sql::Connection* con, int taskID, const std::string& status);

void insertDataToAssignedTasks(sql::Connection* con, int taskID, int employeeID);

class Task {
public:
    Task(const std::string& taskName, const std::string& taskDescription, const std::string& taskPriority, const std::string& taskStartDate, const std::string& taskEndDate, const std::string& taskStatus, int projectID);

    void insertDataToDatabase(sql::Connection* con);   

private:
    std::string name;
    std::string description;
    std::string priority;
    std::string startDate;
    std::string endDate;
    std::string status;
    int projectID;
};
