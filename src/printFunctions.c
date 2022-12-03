#define WIN
// #define LIN

#ifdef LIN
#include "../inc/printFunctions.h"

#else
#include "..\inc\printFunctions.h"

#endif

/* Functions section */
void printHelp(void) {
    printf("It shows temperature stats for the period (month or year).\n");
    printf("Supported keys:\n");
    printf("-f | --file <path>\t Specify the path to the *.scv file;\n");
    printf("[-h | --help]\t\t Help section;\n");
    printf("[-m | --month]\t\t Specify interested month (default - the year);\n");
    printf("[-l | --log]\t\t Turns on printing errors in the file (default - off);\n");
    printf("[-e | --errors]\t\t Turns on printing errors in the console (default - off).\n");
}

void printName(void) {
    printf("                        __        __             _    __          __          ___     \n");
    printf("   ____ ___  ____ _____/ /__     / /_  __  __   | |  / /___ _____/ /___  ____<  /_  __\n");
    printf("  / __ `__ \\/ __ `/ __  / _ \\   / __ \\/ / / /   | | / / __ `/ __  / __ \\/ ___/ / / / /\n");
    printf(" / / / / / / /_/ / /_/ /  __/  / /_/ / /_/ /    | |/ / /_/ / /_/ / /_/ (__  ) / /_/ / \n");
    printf("/_/ /_/ /_/\\__,_/\\__,_/\\___/  /_.___/\\__, /     |___/\\__,_/\\__,_/\\____/____/_/\\__, /  \n");
    printf("                                    /____/                                   /____/   \n");
    printf("\n");
}

void printStartEnd(void) {
    printf("===================================================\n");
}

void printSeparator(void) {
    printf("|-------------------------------------------------|\n");
}

void printHead(void) {
    printStartEnd();
    printf("|             |            Temperature            |\n");
    printf("|    Month    |-----------------------------------|\n");
    printf("|             |    Min    |  Average  |    Max    |\n");
}

void printSeparatorLong(void) {
    printSeparator();
    printf("|                      * * *                      |\n");
    printSeparator();
}

void printData_month(char *month, int Tmin, float Tmid, int Tmax) {
    printf("|  %-9s  |    %-3d    |  %-6.2f   |    %-3d    |\n", month, Tmin, Tmid, Tmax);
}

void printData_year(int year, int Tmin, float Tmid, int Tmax) {
    printf("|  Year: %4d |    %-3d    |  %-6.2f   |    %-3d    |\n", year, Tmin, Tmid, Tmax);
}

void printNOdata(char *month) {
    printf("|  %-9s  |     >>> No data available <<<     |\n", month);
}
