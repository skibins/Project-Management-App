#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cppconn/connection.h>

// =========================
// ---- DB CONNECTION ----
// =========================

// Establishes connection to the database
sql::Connection* connectToDatabase();
#endif
