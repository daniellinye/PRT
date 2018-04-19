CC = g++

CompileParms = -c -Wall -std=c++11
CXXFLAGS = -c -Wall -std=c++11

OBJS = Cell.o CellAddress.o Range.o Sheet.o SheetView.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Sheet
	
Cell.o: Cell.cpp Cell.h
	$(CC) $(CompileParms) Cell.cpp
	
CellAddress.o: CellAddress.cpp CellAddress.h
	$(CC) $(CompileParms) CellAddress.cpp
	
Sheet.o: Sheet.cpp Sheet.h
	$(CC) $(CompileParms) Sheet.cpp

Range.o: Range.cpp Range.h
	$(CC) $(CompileParms) Range.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp
