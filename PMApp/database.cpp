#include "database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <stdlib.h>

// =========================
// ---- DB CONNECTION ----
// =========================

// Database connection parameters
const std::string server = "tcp://127.0.0.1:3306";
const std::string username = "root";
const std::string password = "ZAQ!2wsx";

// Establishes connection to the database
sql::Connection* connectToDatabase() {
    sql::Driver* driver;
    sql::Connection* con;

    try {
        // Creating a driver instance to establish the connection
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        // Setting the schema (database) to work with
        con->setSchema("pm_db");

        return con;
    }
    catch (sql::SQLException e) {
        // Handling connection errors
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        exit(1);
    }
}