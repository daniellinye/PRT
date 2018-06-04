#!/bin/sh

CC = g++
CFLAGS = -fPIC -g -Wall -std=c++11 -lcurses
LDFLAGS = -shared -Wl,-soname,libsheet.so.1
OBJS =  Range.o  SheetView.o main.o Sheet.o


final: all
	$(CC) -std=c++11 -lcurses -Wall -I. -L. main.cpp -lsheet -lcurses -o Sheet
	#after this do: LD_LIBRARY_PATH=.
	#then ./Sheet

all: clean Compile
	$(CC) $(LDFLAGS) $(CFLAGS) -o libsheet.so.1.0 *.o
	ln -sf libsheet.so.1.0 libsheet.so.1
	ln -sf libsheet.so.1 libsheet.so
 
Compile:
	$(CC) $(CFLAGS) -c *.cpp

clean:
	rm -f $(OBJS) *.o
	rm -f *.so
