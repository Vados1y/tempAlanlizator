#include <unistd.h>
#include <getopt.h>
#include "tempFunctions.h"
#include "printFunctions.h"

extern void readFile(FILE* f);
bool isCsv(char *filename);
void startPrint(void);

bool    isLog = false,
        isErrors = false;

char* filename;

FILE *logFile = NULL;

int main(int argc, char *argv[]){

    int rez = 0, option_index = -1;
    int month = 0;
    
    FILE *file = NULL;

    const char* short_options = "hf:m:le";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"file", required_argument, NULL, 'f'},
        {"month", required_argument, NULL, 'm'},
        {"log", no_argument, NULL, 'l'},
        {"errors", no_argument, NULL, 'e'},
        {NULL, 0, NULL, 0}
    };

    opterr = 0;     // Off warning message
    printName();    // Print the author info
    while (-1 != (rez = getopt_long(argc, argv, short_options, long_options, &option_index)))
    {
        switch (rez) {
            /* HELP */
            case 'h':
                printHelp();
                return 0;
                break;

            /* MONTH CHOOSE */
            case 'm':
                    month = atoi(optarg);
                    if ((month < 1) || (month > 12)) {
                        printf("Month error! Please, select the month from 1 to 12.\nType -h or --help for help.\n");   // +
                        return 1;
                    }
                break;

            /* FILENAME SELECT */
            case 'f':
                filename = optarg;
                if (isCsv (filename))       {printf("Selected file: %s\n", filename);}
                else                        {printf("File error! The file extension isn't .csv\n"); return 1;}  // +
                break;
            
            /* LOG ERRORS */
            case 'l':
                isLog = true;
                logFile = fopen("errors_log.log", "a");
                break;

            /* PRINT ERRORS */
            case 'e':
                isErrors = true;
                break;

            /* WRONG ARGUMENT */
            case '?':
                printf("Wrong argument. Type --help or -h for help.\n");    // +
                return 1;
                break;
        }
        option_index = -1;
    }

    file = fopen(filename, "r");
    if (NULL == file){
        printf("File error! File %s doesn't exist. Try another file.\n", filename);     // +
        return 1;
    }
    else    printf("File %s read successfully!\n\n", filename); // +

    readFile(file);
    if (isErrors)   printf("\n");
    printData(month);
    fclose(file);
    if (isLog)  fclose(logFile);
    printf ("\n");
	return 0;
}

bool isCsv(char *filename) {
    bool isEx = false;
    char symbol;
    int i = 0;
    do
    {
        symbol = *(filename + i++);
        if (symbol == '.')      isEx = true;
        if (symbol == 92 || symbol == '/')     isEx = false;

        if (isEx) {
            if (*(filename + i) == 'c' && *(filename + i + 1) == 's' && *(filename + i + 2) == 'v') {
                return true;
                break;
            }
        }

        if (i > 100) {
            return false;
            break;
        }

    } while (true);
}
