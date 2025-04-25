#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

#include "../include/common.h"
#include "../include/parse.h"


// List all the employees in the database
int listEmployees(struct Employee **employees, int numEmployees){
    for(int i = 0; i < numEmployees; i++){
        printf("[+] Employee ID: %d\n", (*employees)[i].employeeId);
        printf("[-] Name: %s\n", (*employees)[i].name);
        printf("[-] Last Name: %s\n", (*employees)[i].lastName);
        printf("[-] Age: %d\n", (*employees)[i].edad);
        printf("[-] Sex: %s\n", (*employees)[i].sex ? "Male" : "Female");
    }
    printf("[+] ------------------------------------- [+] \n\n");

    return STATUS_SUCCESS;
}


// List a single employee in the database
int listEmployee(struct Employee **employees){
    int numEmployee;
    printf("Which employee do you wanna list?: ");
    scanf("%d", &numEmployee);

    printf("[+] Employee ID: %d\n", (*employees)->employeeId);
    printf("[-] Name: %s\n", (*employees)[numEmployee].name);
    printf("[-] Last Name: %s\n", (*employees)[numEmployee].lastName);
    printf("[-] Age: %d\n", (*employees)[numEmployee].edad);
    printf("[-] Sex: %s\n", (*employees)[numEmployee].sex ? "Male" : "Female");

    return STATUS_SUCCESS;
}

// Edit a single Employee in the database. 
int editEmployee(struct Employee **employees){
    int numEmployee;
    printf("Which employee do you wanna list?: ");
    scanf("%d", &numEmployee);
    printf("[+] Employee ID: %d\n", numEmployee);
    
    printf("[-] Curren Name: %s\n", (*employees)[numEmployee].name);
    printf("[-] New Name: ");
    scanf("%s", (*employees)[numEmployee].name);
    
    printf("[-] Current Last Name: %s\n", (*employees)[numEmployee].lastName);
    printf("[-] New Last Name: ");
    scanf("%s", (*employees)[numEmployee].lastName);
    
    printf("[-] Current Age: %d\n", (*employees)[numEmployee].edad);
    printf("[-] New Age: ");
    scanf("%d", &(*employees)[numEmployee].edad);

    printf("[-] Current Sex: %s\n", (*employees)[numEmployee].sex ? "Male" : "Female");
    printf("[-] New Sex: ");
    printf("Sexo (H) o (M): ");
    char sex;
    scanf(" %c", &sex);
    if(sex == 'H'){
        (*employees)[numEmployee].sex = true;
    }else{
        (*employees)[numEmployee].sex = false;
    } 

    return STATUS_SUCCESS;

}

// Create a new employee in the database
int createNewEmployee(struct Employee **employees, struct databaseHeader **headerInfo){

    (*headerInfo)->employees++;
    int numEmployees = (*headerInfo)->employees;
    struct Employee *tmp = realloc(*employees, sizeof(Employee) * numEmployees);
    *employees = tmp;

    printf("%d \n", numEmployees);
    printf("EmpleadoId: %d \n", ((*employees)[numEmployees -1 ].employeeId = numEmployees -1));
    
    printf("Nombre: ");
    scanf("%s", (*employees)[numEmployees -1].name);
    
    printf("Apellido: ");
    scanf("%s", (*employees)[numEmployees -1].lastName);
    
    printf("Edad: ");
    scanf("%d", &(*employees)[numEmployees -1].edad);
    
    printf("Sexo (H) o (M): ");
    char sex;
    scanf(" %c", &sex);

    if(sex == 'H'){
        (*employees)[numEmployees -1].sex = true;
    }else{
        (*employees)[numEmployees -1].sex = false;
    }

    return STATUS_SUCCESS;
}

// Delete an Employee in the database. 
int deleteEmployee(struct Employee **employees, struct databaseHeader **headerInfo){
    int numEmployee;
    printf("Which employee do you wanna to delete?: ");
    scanf("%d", &numEmployee);

    memmove(&(*employees)[numEmployee], &(*employees)[numEmployee + 1 ], sizeof(struct Employee) * ((*headerInfo)->employees - numEmployee - 1));

    (*headerInfo)->employees--;

    struct Employee *tmp = realloc(*employees, sizeof(struct Employee) * (*headerInfo)->employees);
    
    if(tmp != NULL ){
        *employees = tmp; 
    }else {
        printf("Error");
    }

    printf("employees %d - tmp %d\n", sizeof(*employees), sizeof(*tmp));

    return STATUS_SUCCESS;

}


// Save the database  
int saveDatabase(struct Employee **employees, struct databaseHeader **header, char *db_name){

    int fd_database;
    char *databaseName = malloc(15);
    strcpy(databaseName, db_name);
    
    fd_database = open(databaseName, O_WRONLY | O_CREAT, 0644);

    if(fd_database == -1 ){
        perror("open");
        exit(1);
    }
    
    (*header)->filelenght = (sizeof(Employee) * (*header)->employees) + sizeof(databaseHeader);
    
    write(fd_database, header, sizeof(databaseHeader));
    write(fd_database, employees, sizeof(Employee) * (*header)->employees);
    
    off_t current_pos = lseek(fd_database, 0, SEEK_CUR);
    ftruncate(fd_database, current_pos);

    close(fd_database);

    return STATUS_SUCCESS;
    
}


int newDatabase(char *db_name){

    printf("[+] How many employees?  \n");
    int numEmployees;
    scanf("%d", &numEmployees);

    struct Employee *employees = calloc(numEmployees, sizeof(struct Employee));
    struct databaseHeader *headerInfo = malloc(sizeof(databaseHeader));


    char *db_filename = malloc(sizeof(db_name));
    strcpy(db_filename, db_name);
    
    int fd_database;


    fd_database = open(db_filename, O_WRONLY | O_CREAT, 0644);
    if(fd_database == -1){
        perror("open");
        return EXIT_FAILURE;
    }

    headerInfo->version = 1;
    headerInfo->employees = numEmployees;
    headerInfo->filelenght = (sizeof(Employee) * numEmployees) + sizeof(databaseHeader);

    for(int i = 0; i < numEmployees; i++){
        employees[i].employeeId = i;
        printf("EmpleadoId: %d \n", employees[i].employeeId);
        
        printf("Nombre: ");
        scanf("%s", employees[i].name);
        
        printf("Apellido: ");
        scanf("%s", employees[i].lastName);
        
        printf("Edad: ");
        scanf("%d", &employees[i].edad);
        
        printf("Sexo (H) o (M): ");
        char sex;
        scanf(" %c", &sex);
    
        if(sex == 'H'){
            employees[i].sex = true;
        }else{
            employees[i].sex = false;
        }
    }

    write(fd_database, headerInfo, sizeof(headerInfo));

    write(fd_database, employees, sizeof(Employee) * numEmployees);

    close(fd_database);
    free(employees);
    free(headerInfo);

}

// Informative Menu
void menu(){

    printf("[+] ------- Welcome to database manager ------- [+] \n\n");
    printf("[1] ------- List all users ------- [1] \n");
    printf("[2] ------- List a users ------- [2] \n");
    printf("[3] ------- Edit a user ------- [3] \n");
    printf("[4] ------- Create new user ------- [4] \n");
    printf("[5] ------- Delete a user ------- [5] \n");
    printf("[6] ------- Save current database ------- [6] \n");
    printf("[7] ------- Delete current database ------- [7] \n");
    printf("[8] ------- Print employees menu ------- [8] \n");
    printf("[9] ------- Salir ------- [9] \n");

}