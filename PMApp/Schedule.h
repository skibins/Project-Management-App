#pragma once

#include <string>
#include <mysql_connection.h>

std::string getScheduleByID(sql::Connection* con, int scheduleID);

void updateScheduleActualEndDate(sql::Connection* con, int scheduleID, const std::string& actualEndDate);

void insertDataToSchedules(sql::Connection* con, int projectID, const std::string& plannedEndDate, const std::string& actualEndDate);

class Schedule
{
public:
	Schedule(int projectID, const std::string& schedulePlannedEndDate, const std::string& scheduleActualEndDate);

	void insertDataToDatabase(sql::Connection* con);

private:
	int projectID;
	std::string plannedEndDate;
	std::string actualEndDate;
};

