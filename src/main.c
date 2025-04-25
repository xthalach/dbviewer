#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include "../include/parse.h"
#include "../include/functions.h"

// Main function 
int main (int argc, char *argv[]){

    //Check arguments
    if(argc < 2 ){
        printf("Usage Import Dabase: %s -f <database path>\n", argv[0]);
        printf("Usage Create Dabase: %s -d <database path>", argv[0]);
        return EXIT_FAILURE;
    }else if(strcmp(argv[1], "-f") == 0){
        // Declarin and Initilazing variables, crec que es pot utilizar el fgets per a limitar el size 
        struct Employee *empleados;
        struct databaseHeader *headerInfo = calloc(1, sizeof(databaseHeader));

        if(strlen(argv[2]) > 16 || strlen(argv[2]) == 0){
            printf("The name size of the database is too long, <32bytes>!\n");
            return EXIT_FAILURE;
        }
        

        if(parseDatabase(&empleados, &headerInfo, argv[2]) == EXIT_FAILURE ) {
            perror("parseDatabase Error\n");
            exit(1);
        }
        
        int opcion;
        menu();            
    
        do {
            printf("[-->] ");
            scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    printf("[+] ------- Lising all the users ------- [+]\n");
                    if(listEmployees(&empleados, headerInfo->employees) == EXIT_FAILURE ){
                        perror("listEmployees Error");
                        return EXIT_FAILURE;
                    }
                break;
                case 2:
                    printf("[+] ------- List a user ------- [+] \n");\
                    if(listEmployee(&empleados) == EXIT_FAILURE ){
                        perror("listEmployee error");
                        return EXIT_FAILURE;
                    }

                break;
                case 3:
                    printf("[+] ------- Editing a user ------- \n");
                    if(editEmployee(&empleados) == EXIT_FAILURE ){
                        perror("editEmployee Error");
                        return EXIT_FAILURE;
                    }

                break;
                case 4:
                    printf("[4] ------- Create new user ------- [4] \n");
                    if(createNewEmployee(&empleados, &headerInfo) == EXIT_FAILURE ){
                        perror("createNewEmployee Error");
                        return EXIT_FAILURE;
                    }

                break;
                case 5:
                    printf("[+] ------- Deleting a user ------- \n");
                    if(deleteEmployee(&empleados, &headerInfo) == EXIT_FAILURE ) {
                        perror("deleteEmployee Error");
                        return EXIT_FAILURE;
                    }

                break;
                case 6:
                    printf("[+] ------- Saving database ------- \n");
                    if(saveDatabase(&empleados, &headerInfo, argv[2]) == EXIT_FAILURE ){
                        perror("saveDatabase error");
                        return EXIT_FAILURE;
                    }

                break;
                case 7:
                    printf("[+] ------- Delete current database ------- \n");

                break;
                case 8:
                    menu();
                break;
                case 9:
                    printf("[+] ------- Quitting ------- \n");
                break;
                default:
                    printf("[!] -------  Error, number is not in the menu ------- [!] \n");
                break;
            }
        }while(opcion != 9);
    
        free(empleados);
        free(headerInfo);     

    }else if(strcmp(argv[1], "-d") == 0){
        printf("[+] ------- Welcome to database manager ------- [+] \n\n");
        if(strlen(argv[2]) > 16 || strlen(argv[2]) == 0){
            printf("The name size of the database is too long, <32bytes>!\n");
            return EXIT_FAILURE;
        }
        // Falta comprobar la mida del nom del arxiu de la bbdd. 
        if(newDatabase(argv[2]) == EXIT_FAILURE ){
            perror("newDatabase Error\n");
            return EXIT_FAILURE;
        }
        
    }else {
        printf("Usage Import Dabase: %s -f <database path>\n", argv[0]);
        printf("Usage Create Dabase: %s -d <database path>", argv[0]);
        return EXIT_FAILURE;
    }


    
    return 0;
}