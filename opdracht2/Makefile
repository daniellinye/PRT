CC = g++

CompileParms = -c -Wall -std=c++11
LDFLAGS = -lncurses

OBJS = Cell.o CellAddress.o Range.o Sheet.o SheetView.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Sheet $(LDFLAGS)

Cell.o: Cell.cpp
	$(CC) $(CompileParms) Cell.cpp

CellAdress.o: CellAdress.cpp
	$(CC) $(CompileParms) CellAddress.cpp

Range.o: Range.cpp
	$(CC) $(CompileParms) Range.cpp

Sheet.o:  Sheet.cpp
	$(CC) $(CompileParms) Sheet.cpp

SheetView.o:  SheetView.cpp
	$(CC) $(CompileParms) SheetView.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp
