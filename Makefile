all: main

main: main.o tempFunctions.o printFunctions.o
	gcc main.o tempFunctions.o printFunctions.o -o main

main.o: main.c
	gcc -c main.c

tempFunctions.o: tempFunctions.c
	gcc -c tempFunctions.c

printFunctions.o: printFunctions.c
	gcc -c printFunctions.c

clean:
	del *.o *.exe