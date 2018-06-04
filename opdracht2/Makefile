#!/bin/sh

CC = gcc
<<<<<<< HEAD
CFLAGS = -fPIC -g -Wall -std=c++11 -lcurses
LDFLAGS =  -shared
OBJS = Sheet.o Range.o SheetView.o main.o 
export LD_LIBRARY_PATH=.

final: all
	$(CC) -std=c++11 -Wall  -I/mnt/f/Github/PRT/opdracht2  -L/mnt/f/Github/PRT/opdracht2 -o Sheet main.cpp -llibSheet -lcurses

all: clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o libSheet.so $(LDFLAGS)

libSheet.so: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

Range.o: Range.cpp
	$(CC) $(CFLAGS) -c Range.cpp

Sheet.o:  Sheet.cpp
	$(CC) $(CFLAGS) -c Sheet.cpp

SheetView.o:  SheetView.cpp
	$(CC) $(CFLAGS) -c SheetView.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) *.o
	rm -f $(OBJS) *.so
=======
CFLAGS = -fPIC -g -Wall -std=c++11 -lncurses
LDFLAGS = -shared 
OBJS =  Range.o  SheetView.o main.o Sheet.o

final: all
	$(CC) $(CFLAGS)  -I/mnt/d/Github/PRT/opdracht2 -L-l/mnt/d/Github/PRT/opdracht2/ -o Sheet main.cpp

all: clean $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o Sheet.so $(OBJS) 
 
clean:
	rm -f $(OBJS) *.o

Range.o: Range.cpp Range.h
	$(CC) $(CFLAGS) -c Range.cpp $(LDFLAGS)

Sheet.o:  Sheet.cpp Sheet.h
	$(CC) $(CFLAGS) -c Sheet.cpp $(LDFLAGS)

SheetView.o:  SheetView.cpp SheetView.h
	$(CC) $(CFLAGS) -c SheetView.cpp $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp $(LDFLAGS)
>>>>>>> aa3f353064ed48bd88c6b928addac994f2430baf
