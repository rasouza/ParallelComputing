CC = gcc
CFLAGS = -fopenmp -O2 -Wall -ansi -pedantic -Wno-unused-result -std=c11 -lm

all: main

main: main.o ppm.o vector.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c vector.h ppm.h
	$(CC) -o $@ -c $< $(CFLAGS)

vector.o: vector.c ppm.h vector.h
	$(CC) -o $@ -c $< $(CFLAGS)

ppm.o: ppm.c ppm.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o


