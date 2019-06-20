#!/bin/sh

CC = g++
CFLAGS = -fPIC -g -Wall -std=c++11
LDFLAGS = -shared -Wl,-soname,libsheet.so.1 
OBJS =  main.o Range.o Sheetview.o CellAddress.o Sheet.o Cell.o

final: all
	$(CC) -std=c++11 -lcurses -Wall -I. -L. main.cpp -lsheet -lcurses -o Sheet
	$(export LD_LIBRARY_PATH=.)
	#after this do: export LD_LIBRARY_PATH=.
	#then ./Sheet

all: clean Compile
	$(CC) $(LDFLAGS) $(CFLAGS) -o libsheet.so.1.0 $(OBJS) -lcurses
	ln -sf libsheet.so.1.0 libsheet.so.1
	ln -sf libsheet.so.1 libsheet.so
 
Compile:
	$(CC) $(CFLAGS) -c *.cpp -lcurses

clean:
	rm -f $(OBJS) *.o
	rm -f *.so
	rm -f *.0
	rm -f *.1
