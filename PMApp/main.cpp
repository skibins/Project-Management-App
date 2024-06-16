#include <iostream>
#include <windows.h>
#include "menu.h"

using namespace std;

int main() {
    // Establish connection to the database
    sql::Connection* con = connectToDatabase();

    // =========================
    // ------- MAIN MENU -------
    // =========================
    
    showupScreen();
    
    int option;
    // Show main menu
    while (true) {
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| Choose an option: [1-7]" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        cout << "| 1 | Projects" << endl; Sleep(50);
        cout << "| 2 | Tasks" << endl; Sleep(50);
        cout << "| 3 | Employees" << endl; Sleep(50);
        cout << "| 4 | Project Managers" << endl; Sleep(50);
        cout << "| 5 | Schedules" << endl; Sleep(50);
        cout << "| 6 | Reports" << endl; Sleep(50);
        cout << "| 7 | Exit" << endl; Sleep(50);
        cout << "|------------------------------------" << endl; Sleep(50);
        
        cout << ":";
        cin >> option;
        system("cls");
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
