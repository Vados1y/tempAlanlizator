all: main

main: main.o tempFunctions.o
	gcc main.o tempFunctions.o -o main

main.o: main.c
	gcc -c main.c

tempFunctions.o: tempFunctions.c
	gcc -c tempFunctions.c

clean:
	del *.o *.exe