#ifndef PRINTFUNCTIONS_H

#define PRINTFUNCTIONS_H
#include <stdio.h>

void printHelp(void);
void printName(void);
void printHead(void);
void printSeparatorLong(void);
void printSeparator(void);
void printData_month(char *month, int Tmin, float Tmid, int Tmax);
void printData_year(int year, int Tmin, float Tmid, int Tmax);
void printStartEnd(void);
void printNOdata(char *month);


#endif
