#pragma once

#include <string>
#include <mysql_connection.h>
#include "database.h"

std::string getReportByProjectID(sql::Connection* con, int reportID);
void updateReportCompletedTasks(sql::Connection* con, int reportID, int numberOfCompletedTasks);

class Report
{
public:
	Report(sql::Connection* con, int projectID, const std::string& newOtherInformation);

	void insertDataToDatabase(sql::Connection* con);

private:
	int projectID;
	int managerID;
	int numberOfCompletedTasks;
	std::string otherInformation;
};

