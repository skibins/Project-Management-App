#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cppconn/connection.h>

/**
 * Method to connect to our database.
 */
sql::Connection* connectToDatabase();

/**
 * Method to insert data to our table user.
 * @param con Connection object used for our db connection.
 * @param name User name.
 * @param age User age.
 */
void insertDataToUsers(sql::Connection* con, const std::string& name, int age);

#endif