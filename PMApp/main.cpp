#include <iostream>
#include "menu.h"

using namespace std;

int main() {
    // Establish connection to the database
    sql::Connection* con = connectToDatabase();

    // =========================
    // ------- MAIN MENU -------
    // =========================

    int option;

    while (true) {
        cout << "MAIN MENU" << endl;
        cout<<endl;

        cout << "Choose an option:" << endl;
        cout << "1. Projects" << endl;
        cout << "2. Tasks" << endl;
        cout << "3. Employees" << endl;
        cout << "4. Project Managers" << endl;
        cout << "5. Schedules" << endl;
        cout << "6. Reports" << endl;
        cout << "7. Exit" << endl;
        
        cout << ":";
        cin >> option;
        switch (option) {
        case 1:
            projectsMenu();
            break;
        case 2:
            tasksMenu();
            break;
        case 3:
            employeesMenu();
            break;
        case 4:
            projectManagersMenu();
            break;
        case 5:
            schedulesMenu();
            break;
        case 6:
            reportsMenu();
            break;
        case 7:
            exit(0);
        default:
            cout << "Invalid option, try again." << endl;
        }

    }

    // Closing the database connection
    delete con;

    return 0;
}
