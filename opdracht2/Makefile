#!/bin/sh

CC = gcc
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