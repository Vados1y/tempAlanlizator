#include "tempFunctions.h"

#define paramNumbers 6

bool correctData_check(int y, int mon, int d, int h, int min, int t){
    bool error = false;
    
    /* Leap year CHECK */
    if (y % 4 == 0 && mon == 2 && d > 29)       error = true;   // if leap year and > 29 days in febr
    if (y % 4 != 0 && mon == 2 && d > 28)       error = true;   // if not leap year and > 28 days in febr

    /* Month count CHECK */
    if (mon < 1 || mon > 12)                    error = true;

    /* Hours CHECK */
    if (h < 0 || h > 23)                        error = true;

    /* Minutes CHECK */
    if (min < 0 || min > 59)                    error = true;

    /* Temperature CHECK */
    if (t < -99 || t > 99)                      error = true;

    /* Days in months CHECK */
    switch (mon)
    {
    case 1:     // Jun
        if (d < 0 || d > 31)    error = true;   break;
    case 3:     // March
        if (d < 0 || d > 31)    error = true;   break;
    case 4:     // Apr
        if (d < 0 || d > 30)    error = true;   break;
    case 5:     // May
        if (d < 0 || d > 31)    error = true;   break;
    case 6:     // Jun
        if (d < 0 || d > 30)    error = true;   break;
    case 7:     // July
        if (d < 0 || d > 31)    error = true;   break;
    case 8:     // Aug
        if (d < 0 || d > 31)    error = true;   break;
    case 9:     // Sep
        if (d < 0 || d > 30)    error = true;   break;
    case 10:    // Oct
        if (d < 0 || d > 31)    error = true;   break;
    case 11:    // Nov
        if (d < 0 || d > 30)    error = true;   break;
    case 12:    // Dec
        if (d < 0 || d > 31)    error = true;   break;
    default:
        if (d < 0 || d > 31)    error = true;   break;
    }

    return error;
}


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
            if (correctData_check(year, month, day, hour, minute, temp)) {
                printf("Error in line %2d\n", line);
            }
            else {
                printf("Line %2d >>>  year:%4d\tmonth:%2d\tday:%2d\thour:%2d\tminute:%2d\ttemp:%3d\n", line, year, month, day, hour, minute, temp);
            }
        }

    

    }
}