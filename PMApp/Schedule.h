#pragma once

#include <string>
#include <mysql_connection.h>

std::string getScheduleByProjectID(sql::Connection* con, int projectID);

void updateScheduleActualEndDate(sql::Connection* con, int scheduleID, const std::string& actualEndDate);

class Schedule
{
public:
	Schedule(sql::Connection* con, int projectID, const std::string& scheduleActualEndDate);

	void insertDataToDatabase(sql::Connection* con);

private:
	int projectID;
	std::string plannedEndDate;
	std::string actualEndDate;
};

