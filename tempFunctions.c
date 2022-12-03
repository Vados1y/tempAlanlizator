#include "tempFunctions.h"
#include "printFunctions.h"

#define paramNumbers 6
#define getTime nowTime=time(NULL)
#define putTime ctime(&nowTime)

extern bool isErrors;
extern bool isLog;
extern FILE *logFile;
extern char* filename;

typedef struct
{
    int64_t sum;
    uint32_t n;    
    int8_t tMax;
    int8_t tMin;
} tempDataType;

char monthNames[12][10] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
    };


static tempDataType tempData[13] = {        // 0 - year, 1-12 - months
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    {0, 0, -100, 100},
    }; 

static int year;

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
    int month, day, hour, minute, temp;
    int line = 1, symbolsCount = -1;
    char buffer[21] = "*********************";  // Fill array with '*'
    char ch;
    long int nowTime;

    if (isLog) {
        getTime;
        fprintf(logFile, "\nFile updated on: %s", putTime);
        fprintf(logFile, "File: %s\n", filename);
    }

    for (line = 1; fscanf(f, "%20[^\n]s", buffer) != EOF; line++) // Loop by lines
    {
        /* Extra symbols check */
        do {
            ch = fgetc(f);
            symbolsCount++;
        } while (ch != '\n' && ch != EOF);
        
        if (symbolsCount > 0) {
            if (isErrors)   printf(">>> Error in line %d: Too many symbols.\n", line);     // +
            if (isLog)      fprintf(logFile, ">>> Error in line %d: Too many symbols.\n", line);   //+
            symbolsCount = -1;
        }
        symbolsCount = -1;

        /* Fill data in variables */    
        if (sscanf(buffer, "%d%*c%d%*c%d%*c%d%*c%d%*c%d",   // Read numbers and any symbol between
                            &year, &month, &day, &hour, &minute, &temp) != paramNumbers){   // 6 types of data check
            if (isErrors)   printf(">>> Error in line %d: Too few arguments or data syntax error.\n", line);   // +
            if (isLog)      fprintf(logFile, ">>> Error in line %d: Too few arguments or data syntax error.\n", line);     //+
            continue;
        }
        else {
            if (correctData_check(year, month, day, hour, minute, temp)) {
                if (isErrors)    printf(">>> Error in line %d: Data error.\n", line);   // +
                if (isLog)      fprintf(logFile, ">>> Error in line %d: Data error.\n", line); // +
            }
            else {

                /* Fill the data for months */
                tempData[month].sum += temp;
                tempData[month].n += 1;
                if (temp < tempData[month].tMin)    tempData[month].tMin = temp;
                if (temp > tempData[month].tMax)    tempData[month].tMax = temp;

                /* Fill the data for year */
                tempData[0].sum += temp;
                tempData[0].n++;
                if (temp < tempData[0].tMin)        tempData[0].tMin = temp;
                if (temp > tempData[0].tMax)        tempData[0].tMax = temp;
            }
        }
    }
    if (isLog)  fprintf(logFile, "*** End of file ***\n");
}

void printData(int chosenMonth) {
    if (chosenMonth == 0 && tempData[0].n > 0) {
        /* Chosen year */

        /* Head */
        printHead();

        /* Months data print */
        for (int i = 0; i < 12; i++) {
            if (tempData[i + 1].n > 0) {    // If data for the month
                printSeparator();
                printData_month(monthNames[i], tempData[i + 1].tMin, (float)tempData[i + 1].sum / (float)tempData[i + 1].n, tempData[i + 1].tMax);
            }

            else {                          // If no data for the month
                printSeparator();
                printNOdata(monthNames[i]);
            }                                                         
        }

        printSeparatorLong();

        /* Year data print */
        printData_year(year, tempData[0].tMin, (float)tempData[0].sum / (float)tempData[0].n, tempData[0].tMax);
        printStartEnd();
    }

    else if (chosenMonth != 0) {
        /* Chosen month */

        /* Head */
        printHead();

        /* Month data print */
        if (tempData[chosenMonth].n > 0) {
            printSeparator();
            printData_month(monthNames[chosenMonth], tempData[chosenMonth].tMin, (float)tempData[chosenMonth].sum / (float)tempData[chosenMonth].n, tempData[chosenMonth].tMax);
        }

        /* If no data for the month */
        else {
            printSeparator();
            printNOdata(monthNames[chosenMonth]);
        }
        printStartEnd();
    }

    /* If no any data */
    else        printf("No any data available\n");
}