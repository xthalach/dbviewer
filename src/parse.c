#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "../include/common.h"
#include "../include/parse.h"

int parseDatabase(struct Employee **employees, struct databaseHeader **headerInfo, char *nameDatabase){

    int fd_database;

    fd_database = open(nameDatabase, O_RDONLY);
    if(fd_database == -1){
        perror("open");
        return -1;
    }

    // From the import database get header information.    
    read(fd_database, *headerInfo, sizeof(struct databaseHeader));

    // Allocate the memory for all the employees.
    *employees = calloc((*headerInfo)->employees, sizeof(struct Employee));

    read(fd_database, *employees, sizeof(struct Employee));

    close(fd_database);

    return STATUS_SUCCESS;
}