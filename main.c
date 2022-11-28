#include <stdio.h>
#include <unistd.h>
#include "tempFunctions.h"

extern void readFile(FILE* f);

int main(int argc, char *argv[]){

    int rez = 0;
    int month = -1;
    char* filename;
    FILE *file = NULL;

    opterr = 0; // Off warning message
    while (-1 != (rez = getopt(argc, argv, "hf:m:y")))
    {
        switch (rez) {
            /* HELP */
            case 'h':
                printf("d e s c r i p t i o n.\n");
                break;

            /* MONTH CHOOSE */
            case 'm':
                if (month == -1) {
                    month = atoi(optarg);
                    if ((month < 1) || (month > 12)) {
                        printf("Month error! Type -h for help.\n");
                        return 1;
                    }
                }
                else    printf("You have already selected info for the year!\n");
                break;

            /* FILENAME SELECT */
            case 'f':
                filename = optarg;
                printf("Selected file: %s\n", filename);
                break;

            case 'y':
                if (month == -1)    month = 0;
                else                printf("You have already selected info for the month >%d< !\n", month);
                break;

            /* WRONG ARGUMENT */
            case '?':
                printf("Wrong argument. Type -h for help.\n");
                break;
        }
    }

    file = fopen(filename, "r");
    if (NULL == file){
        printf("File %s not read! Try another file.\n", filename);
        return 1;
    }
    else    printf("File %s read successfully!\n", filename);



    readFile(file);
    printData(month);



    fclose(file);
	return 0;
}


