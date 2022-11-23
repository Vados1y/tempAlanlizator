#include "tempFunctions.h"

#define paramNumbers 6

void readFile(FILE* f){
    int year, month, day, hour, minute, temp;
    int line = 1;
    char buffer[30] = "*****************************"; // Fill array with '*'

    for (line = 1; fscanf(f, "%[^\n]s", buffer) != EOF; line++) // Loop by strings
    {
        while (fgetc(f) != '\n' && fgetc(f) != EOF); // "Eating" '\n' or 'EOF'

        /* Debug buffer out */
        printf("Line %2d:   ", line);
        printf("%s", buffer);
        printf("\n");

        strcpy(buffer, "*****************************"); // Fill array with '*' 
    }
    
    

    
    // printf(">>> %d\n", strlen(buffer));   // +20

    // if (sscanf(buffer, "%d;%d;%d;%d;%d;%d;", &year, &month, &day, &hour, &minute, &temp) != paramNumbers){
    //     printf("Fields ERROR!\n");
    // }
    // else
    //     printf("Great!\n");

    // printf("%d\n", year + 100);
}