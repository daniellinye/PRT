#!/bin/sh

CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = CellFormula.o Cell.o Column.o Sheet.o CellAddress.o Range.o
UIOBJS = SheetController.o SheetView.o EditController.o EditView.o
LDFLAGS = -L. -lsheet -lview -lncurses
LIBFLAGS = -shared

all: clean libsheet.so libview.so Sheet

check: clean libsheet.so libview.so Test

Sheet: main.cc
	$(CC) $(CFLAGS) $< -o $@ $(OBJS) $(LDFLAGS)
	#after this do: export LD_LIBRARY_PATH=.
	#then ./Sheet

Test: test_range.cc
	$(CC) $(CFLAGS) $< -o $@ $(OBJS) $(LDFLAGS)

libsheet.so: $(OBJS)
	$(CC) $(LIBFLAGS) -o $@ $^

libview.so: $(UIOBJS)
	$(CC) $(LIBFLAGS) -o $@ $^

%.o: %.cc
	$(CC) -fPIC -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f Sheet Test libview.so $(OBJS) $(UIOBJS)
