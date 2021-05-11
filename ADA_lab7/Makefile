# makefile for week6 examples

all:	arrays types strings testada cstrings unions lab07

lab07:	lab07.adb
	gnatmake lab07.adb
	gnatbind -x lab07.ali
	gnatlink lab07.ali

testada:  testada.adb
	gnatmake testada.adb

arrays:	arrays.c 
	gcc -o arrays arrays.c 

unions:	unions.c 
	gcc -o unions unions.c 

types:	types.c
	gcc -o types types.c

strings:	strings.cpp
	g++ -o strings strings.cpp

cstrings:	strings.c
	gcc -o cstrings strings.c

clean:
	rm -f arrays types cstrings strings testada unions lab07.ali lab07.o
