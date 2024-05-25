#pragma once

#include <string>
#include <mysql_connection.h>

std::string getProjectByID(sql::Connection* con, int projectID);
std::string getAllProjects(sql::Connection* con);
void updateProjectStatus(sql::Connection* con, int projectID, const std::string& status);

class Project {
public:
    Project(const std::string& projectName, const std::string& projectDescription, const std::string& projectStartDate, const std::string& projectEndDate, const std::string& projectStatus);

    void insertDataToDatabase(sql::Connection* con);

private:
    std::string name;
    std::string description;
    std::string startDate;
    std::string endDate;
    std::string status;
};

