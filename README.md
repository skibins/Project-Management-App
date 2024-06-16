# PMA - Project Management App

## About the Project

PMA (Project Management App) is designed for companies that need a tool to manage projects, document progress, and control information. The application enables the creation and management of projects, tasks, employees, and deadlines. Key features include:
- Creating and managing projects.
- Creating tasks within projects.
- Assigning tasks to employees and projects to project managers.
- Generating reports on projects and schedules.

## Table of Contents

1. [Introduction](#introduction)
2. [System Requirements](#system-requirements)
3. [Installation Guide](#installation-guide)
4. [User Guide](#user-guide)
5. [Admin Guide](#admin-guide)
6. [Developer Guide](#developer-guide)
7. [Common Issues](#common-issues)
8. [License and Legal Information](#license-and-legal-information)
9. [Contact and Support](#contact-and-support)
10. [Attachments](#attachments)

## System Requirements

Operating System: Windows (x64)  
Minimum Hardware Requirements:
  - Processor: Intel Core i3 or equivalent
  - RAM: 4 GB
  - Disk Space: 40 MB
  - Required Space: 10 MB

## Installation Guide

1. Download and install XAMPP from [here](https://www.apachefriends.org/pl/index.html).
2. Download mysql-connector-cpp version 8.3.0 from [here](https://dev.mysql.com/downloads/connector/cpp/).
3. Extract mysql-connector-cpp to the directory `C:\Program Files\libraries` and name the folder `mysql-8.3.0-winx64`.
4. Enable MySQL and Apache modules in the XAMPP package.
5. Open ‘localhost’ in your browser.
6. Create an empty database `pm_db` locally on your machine (database schema for import is included in the project files).
7. Import the database into the previously created `pm_db`.
8. Go to the USER ACCOUNTS tab in the global settings of phpMyAdmin.
9. Add the password “ZAQ!2wsx” for the user named root and host named localhost.
10. In the XAMPP package, select Config next to Apache. From the dropdown menu, choose phpMyAdmin (config.inc.php).
11. In the section /* Authentication type and info */ set the password for the root user to ‘ZAQ!2wsx’. E.g. $cfg['Servers'][$i]['password'] = 'ZAQ!2wsx';
12. Check if the database opens correctly in the browser.
13. Run the PMA application.

## Developer Setup

To configure VS for working with the application, follow the instructions: [Build C/C++ Applications Using MySQL Connector and Visual Studio 2022](https://www.youtube.com/watch?v=a_W4zt5sR1M&t=158s) after installing mysql-connector-cpp.

## User Guide

The application interface is intuitive and consists of the following sections:
- **Projects**: Creating and managing projects.
- **Tasks**: Creating and assigning tasks.
- **Employees**: Managing employees.
- **Project Managers**: Assigning project managers.
- **Schedules**: Creating project schedules.
- **Reports**: Generating project reports.

### Basic Steps for Using the Application

1. **Projects**:
   - Select "Projects".
   - Choose an option from the projects category.
   - Enter the data.
   - Confirm.
2. **Tasks**:
   - Select "Tasks".
   - Choose an option from the tasks category.
   - Enter the data.
   - Confirm.

## Admin Guide

Some options, such as deleting projects, employees, or tasks, are not available in the application interface. In such cases, contact the database administrator to manually delete the data.

## Developer Guide

### Code Structure

**Classes**:
- `Main`: Main application class.
- `Menu`: Class containing menu logic.
- `Database`: Manages database connection.
- `Employee`: Employee class.
- `Project`: Project class.
- `ProjectManager`: Project managers class.
- `Report`: Report class.
- `Schedule`: Schedule class.
- `Task`: Task class.

**Modules**:
- `autofillFuncs`: Contains helper functions automating data entry from the database.

### Best Practices

- Stick to the established application logic rules.
- Maintain code order and clarity.
- Use comments to explain what is being done in various parts of the code.


### Code Structure

**Classes**:
- `Main`: Main application class.
- `Menu`: Class containing menu logic.
- `Database`: Manages database connection.
- `Employee`: Employee class.
- `Project`: Project class.
- `ProjectManager`: Project managers class.
- `Report`: Report class.
- `Schedule`: Schedule class.
- `Task`: Task class.

**Modules**:
- `autofillFuncs`: Contains helper functions automating data entry from the database.

### Best Practices

- Stick to the established application logic rules.
- Maintain code order and clarity.
- Use comments to explain what is being done in various parts of the code.

## Common Issues

1. **The application does not start.**
   - Solution: Check the database connection. Ensure the local MySQL server is running.

2. **Missing libraries libcrypto-3-x64.dll / mysqlcppconn8-2-vs14.dll.**
   - Solution: Find the missing libraries in `C:\libraries\mysql-8.3.0-winx64\lib64` and move them to `C:\Windows\System` or `C:\Windows\System64`.

3. **SQL error while using the application.**
   - Solution: Ensure that the `pm_db` database is correctly imported and has the necessary tables.

## License and Legal Information

PMA is licensed under the MIT License.


## Contact

- Email: [jan.skibins@gmail.com](mailto:jan.skibins@gmail.com)
- LinkedIn: [Jan Skibiński](https://www.linkedin.com/in/jan-skibinski/)
- Email: [paszek0302@gmail.com](mailto:paszek0302@gmail.com)
- LinkedIn: [Sebastian Paszek](https://www.linkedin.com/in/sebastian-paszek-663bb12ba/)
- Email: [michal-bujok@o2.pl](mailto:michal-bujok@o2.pl)
- LinkedIn: [Michał Bujok](https://www.linkedin.com/in/michał-bujok-60b101291/)

## Attachments

- Database to import: [pm_db.sql](https://github.com/skibins/Project-Management-App/blob/master/pm_db.sql)

## Disclaimer

The PMA (Project Management App) has been developed solely for educational purposes. It is intended to demonstrate concepts and practices in project management software development. 

**No Warranty**: The software is provided "as is", without any warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.

**Educational Use Only**: This application is not intended for use in a production environment. It should not be used to manage real-world projects or sensitive information.

**No Support**: Given its educational nature, the PMA does not come with any form of support or maintenance. Users should not expect updates, bug fixes, or assistance in using the application.

By using this software, you acknowledge that it is intended for learning and experimentation, and you accept the risks associated with its use.


