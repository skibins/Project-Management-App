#pragma once

#include <string>
#include <mysql_connection.h>

void displayTasksByEmployeeID(sql::Connection* con, int employeeID);
std::string getEmployeeByID(sql::Connection* con, int employeeID);

class Employee	{
public:
	Employee(const std::string& employeeName, const std::string& employeelastName, const std::string& employeeposition);

	void insertDataToDatabase(sql::Connection* con);

private:
	std::string firstName;
	std::string lastName;
	std::string position;
};

