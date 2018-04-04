CC = g++

CompileParms = -c -Wall -std=c++11

OBJS = Cell.o CellAdress.o Range.o Sheet.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Sheet
	
Cell.o: Cell.cpp
	$(CC) $(CompileParms) Cell.cpp
	
CellAdress.o: CellAdress.cpp
	$(CC) $(CompileParms) CellAdress.cpp
	
Range.o: Range.cpp
	$(CC) $(CompileParms) Range.cpp

Sheet.o:  Sheet.cpp
	$(CC) $(CompileParms) Sheet.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp

