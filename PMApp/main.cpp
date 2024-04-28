#include <iostream>
#include "database.h"

using namespace std;

int main() {
    sql::Connection* con = connectToDatabase();

    insertDataToUsers(con, "Janek", 20);
    insertDataToUsers(con, "Michal", 20);
    insertDataToUsers(con, "Sebastian", 20);

    delete con;

    return 0;
}
