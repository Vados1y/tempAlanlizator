#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "tempFunctions.h"

extern void readFile(FILE* f);

int main(int argc, char *argv[]){

    int rez = 0, option_index = -1;
    int month = 0;
    char* filename;
    FILE *file = NULL;

    const char* short_options = "hf:m:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"file", required_argument, NULL, 'f'},
        {"month", required_argument, NULL, 'm'},
        {NULL, 0, NULL, 0}
    };

    opterr = 0;     // Off warning message
    while (-1 != (rez = getopt_long(argc, argv, short_options, long_options, &option_index)))
    {
        switch (rez) {
            /* HELP */
            case 'h':
                printf("d e s c r i p t i o n.\n");
                break;

            /* MONTH CHOOSE */
            case 'm':
                    month = atoi(optarg);
                    if ((month < 1) || (month > 12)) {
                        printf("Month error! Type -h for help.\n");
                        return 1;
                    }
                break;

            /* FILENAME SELECT */
            case 'f':
                filename = optarg;
                printf("Selected file: %s\n", filename);
                break;

            /* WRONG ARGUMENT */
            case '?':
                printf("Wrong argument. Type -h for help.\n");
                break;
        }
        option_index = -1;
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


