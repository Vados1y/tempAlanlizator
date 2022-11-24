#include "tempFunctions.h"

#define paramNumbers 6

void readFile(FILE* f){
    int year, month, day, hour, minute, temp;
    int line = 1, symbolsCount = -1;
    char buffer[21] = "*********************"; // Fill array with '*'
    char ch;

    for (line = 1; fscanf(f, "%20[^\n]s", buffer) != EOF; line++) // Loop by lines
    {
        /* Extra symbols check */
        do {
            ch = fgetc(f);
            symbolsCount++;
        } while (ch != '\n' && ch != EOF);
        
        if (symbolsCount > 0) {
            printf("Error in line %2d\n", line);
            symbolsCount = -1;
            continue;
        }
        symbolsCount = -1;

        /* Fill data in variables */    
        if (sscanf(buffer, "%d%*c%d%*c%d%*c%d%*c%d%*c%d",   // Read numbers and any symbol between
                            &year, &month, &day, &hour, &minute, &temp) != paramNumbers){   // 6 types of data check
            printf("Error in line %2d\n", line);
        }
        else {
            // printf ("Line %2d +\n", line);
            printf("Line %2d >>>  year:%4d\tmonth:%2d\tday:%2d\thour:%2d\tminute:%2d\ttemp:%3d\n", line, year, month, day, hour, minute, temp);
        }

    

    }
}