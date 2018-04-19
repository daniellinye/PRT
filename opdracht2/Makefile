CC = g++

CompileParms = -c -Wall -std=c++11
LDFLAGS = -lncurses

OBJS = Cell.o CellAddress.o Range.o Sheet.o SheetView.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Sheet $(LDFLAGS)

Cell.o: Cell.cpp Cell.h
	$(CC) $(CompileParms) Cell.cpp

CellAdress.o: CellAdress.cpp CellAdress.h
	$(CC) $(CompileParms) CellAddress.cpp

Range.o: Range.cpp Range.h
	$(CC) $(CompileParms) Range.cpp

Sheet.o:  Sheet.cpp Sheet.h
	$(CC) $(CompileParms) Sheet.cpp

SheetView.o:  SheetView.cpp SheetView.h
	$(CC) $(CompileParms) SheetView.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp
