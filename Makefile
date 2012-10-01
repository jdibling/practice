CC=g++
CFLAGS=-g -Wall -c -std=c++0x
LFLAGS=-Wall

all : practice

practice :	main.o quicksort.o mergesort.o binadd.o
	$(CC) $(LFLAGS) main.o quicksort.o mergesort.o binadd.o -o practice

main.o : main.cpp quicksort.h quicksort.h mergesort.h binadd.o
	$(CC) $(CFLAGS) main.cpp 
	

quicksort.o : quicksort.cpp quicksort.h 
	$(CC) $(CFLAGS) quicksort.cpp


mergesort.o :mergesort.cpp mergesort.h 
	$(CC) $(CFLAGS) mergesort.cpp

binadd.o : binadd.cpp binadd.h 
	$(CC) $(CFLAGS) binadd.cpp


clean :
	rm -f *.o practice

