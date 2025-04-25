#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>

// Struct for database header information 
typedef struct databaseHeader{

    unsigned short version;
    unsigned short employees;
    unsigned int filelenght;

}databaseHeader;

// Struct for the Employees
typedef struct Employee{
    // Class atributes
    int employeeId; 
    char name[16];
    char lastName[16];
    int edad;
    bool sex; // if it's true is male, otherwise female.  

}Employee;

int parseDatabase(struct Employee **employees, struct databaseHeader **headerInfo, char *nameDatabase);

#endif