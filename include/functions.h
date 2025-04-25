#ifndef FUNCTIONS_H
#define FUNCTIONS_H



int listEmployees(struct Employee **employees, int numEmployees);
int listEmployee(struct Employee **employees);
int editEmployee(struct Employee **employees);
int createNewEmployee(struct Employee **employees, struct databaseHeader **headerInfo);
int deleteEmployee(struct Employee **this, struct databaseHeader **headerInfo);
int saveDatabase(struct Employee **this, struct databaseHeader **header, char *db_name);
int newDatabase(char *db_name);
void menu();


#endif