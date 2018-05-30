#!/bin/sh

CC = gcc
CFLAGS = -fPIC -g -c -Wall -std=c++11 -l
LDFLAGS =  -shared -lncurses -Wl,-soname,Sheet.so
OBJS =  Range.o  SheetView.o main.o Sheet.o

all: clean $(OBJS) Sheet.so
	$(CC) $(CFLAGS) $(OBJS) Sheet.so $(LDFLAGS)

clean:
	rm -f $(OBJS) *.o

Range.o: Range.cpp Range.h
	$(CC) $(CFLAGS) Range.cpp $(LDFLAGS)

Sheet.o:  Sheet.cpp Sheet.h
	$(CC) $(CFLAGS) Sheet.cpp $(LDFLAGS)

SheetView.o:  SheetView.cpp SheetView.h
	$(CC) $(CFLAGS) SheetView.cpp $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(LDFLAGS)

Sheet.so: $(OBJS)
	$(CC) $(LDFLAGS) -o Sheet.so $(OBJS) -lc

