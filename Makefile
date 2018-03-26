
CC=g++
CFLAGS=-std=c++11
KONF=-O2

all: project1.out

project1.out: main.o student.o test.o 
	$(CC) main.o student.o test.o -o project1.out

main.o: main.cpp
	$(CC) $(CFLAGS) $(KONF) -c main.cpp

student.o: student.cpp student.h
	$(CC) $(CFLAGS) $(KONF) -c student.cpp

test.o: test.cpp test.h
	$(CC) $(CFLAGS) $(KONF) -c test.cpp

clean:
	rm -rf *o project1.out

