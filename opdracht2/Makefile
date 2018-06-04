#!/bin/sh

CC = gcc
CFLAGS = -fPIC -g -Wall -std=c++11
LDFLAGS =  -shared -lncurses
OBJS = Sheet.o Range.o SheetView.o main.o 

final: all
	$(CC) -std=c++11 -Wall  -I.\  -L.\ -lSheet -lncurses -o Sheet main.cpp 

all: clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) Sheet.so $(LDFLAGS)

clean:
	rm -f $(OBJS) *.o

Range.o: Range.cpp
	$(CC) $(CFLAGS) -c Range.cpp -lncurses

Sheet.o:  Sheet.cpp
	$(CC) $(CFLAGS) -c Sheet.cpp -lncurses

SheetView.o:  SheetView.cpp
	$(CC) $(CFLAGS) -c SheetView.cpp -lncurses

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -lncurses


