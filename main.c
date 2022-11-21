#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int rez = 0;
    int m = 0;
    char* filename;

    opterr = 0;
    while (-1 != (rez = getopt(argc, argv, "hf:m:")))
    {
        switch (rez) {
            /* HELP */
            case 'h':
                printf("d e s c r i p t i o n.\n");
                break;

            /* MONTH CHOOSE */
            case 'm':
                m = atoi(optarg);
                if ((m < 1) || (m > 12)) {
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
    }
	return 0;
}


