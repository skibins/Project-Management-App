#include "database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <stdlib.h>

const std::string server = "tcp://127.0.0.1:3306";
const std::string username = "root";
const std::string password = "";

sql::Connection* connectToDatabase() {
    sql::Driver* driver;
    sql::Connection* con;

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);

        //Name of our database. Please create before building the app.
        con->setSchema("pm_db");

        return con;
    }
    catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        exit(1);
    }
}

void insertDataToUsers(sql::Connection* con, const std::string& name, int age) {
    sql::PreparedStatement* pstmt = nullptr;

    try {
        pstmt = con->prepareStatement("INSERT INTO users(name, age) VALUES(?,?)");
        pstmt->setString(1, name);
        pstmt->setInt(2, age);
        pstmt->execute();
        std::cout << "One User inserted." << std::endl;

        delete pstmt;
    }
    catch (sql::SQLException e) {
        std::cout << "Could not insert data to inventory. Error message: " << e.what() << std::endl;
        exit(1);
    }
}
