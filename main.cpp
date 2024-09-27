#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
    /*
        argc:       Number of Column
        azColName:  Name of Column[i]
        argv[i] :   Value of Column[i]
    */
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    char *sql;

    const char *dbFilename = "data.db";
    int rc = sqlite3_open(dbFilename, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // // SQL statement to create a new table
   sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    // SQL statement to insert data into the table
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS) "  \
         "VALUES (1, 'Paul', 32, 'California'); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS) "  \
         "VALUES (2, 'Allen', 25, 'Texas'); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS, SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20.1646);" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS, SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond', 53);";

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    // SQL Query
    sql = "SELECT * FROM COMPANY;";
    // sql = "SELECT * FROM COMPANY WHERE NAME = 'Paul';";
    // sql = "SELECT * FROM COMPANY WHERE SALARY IS NULL;"; 
    // sql = "SELECT * FROM COMPANY WHERE NAME = 'Paul' AND SALARY IS NULL;";
    
    // Execute SQL statement and display results
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Close the database connection
    sqlite3_close(db);
    return 0;
}
