#pragma once

#include <string>
#include <mysql_connection.h>
#include "database.h"

void insertDataToProjectManagerAssignments(sql::Connection* con, int projectID, int managerID);
std::string getProjectManagerByID(sql::Connection* con, int managerID);
void displayProjectsByManagerID(sql::Connection* con, int managerID);

class ProjectManager {
public:
	ProjectManager(const std::string& newFirstName, const std::string& newLastName);

	void insertDataToDatabase(sql::Connection* con);

private:
	std::string firstName;
	std::string lastName;

};

