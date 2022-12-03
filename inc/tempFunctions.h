#ifndef TEMPFUNCTIONS_H

#define TEMPFUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>

void readFile(FILE* f);
void printData(int);
bool correctData_check(int y, int mon, int d, int h, int min, int t);

#endif
