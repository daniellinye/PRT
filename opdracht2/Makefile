CC = g++

CompileParms = -c -Wall -std=c++11
CXXFLAGS = -c -Wall -std=c++11

OBJS = Cell.o CellAddress.o Range.o Sheet.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Sheet
	
Cell.o: Cell.cpp
	$(CC) $(CompileParms) Cell.cpp
	
CellAddress.o: CellAddress.cpp
	$(CC) $(CompileParms) CellAddress.cpp
	
Sheet.o: Sheet.cpp
	$(CC) $(CompileParms) Sheet.cpp

Range.o: Range.cpp
	$(CC) $(CompileParms) Range.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp

