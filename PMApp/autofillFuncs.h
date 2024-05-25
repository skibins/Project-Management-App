#pragma once

#include <string>
#include <mysql_connection.h>

std::string fillPlannedEndDateFromDatabase(sql::Connection* con, int ScheduleProjectID);

int fillManagerIdFromDatabase(sql::Connection* con, int projectID);

int fillCompletedTasksFromDatabase(sql::Connection* con, int projectID);