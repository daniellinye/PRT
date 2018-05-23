CC = gcc

CompileParms = -c -Wall -std=c++11 -Iinclude
CompileFlags = -fPIC
LDFLAGS = -lncurses -shared

OBJS = Range.o Sheet.o SheetView.o main.o 


Sheet.so: $(OBJS)
	$(CC)  $(OBJS) -o Sheet.so $(CompileFlags) $(LDFLAGS) 

Range.o: Range.cpp
	$(CC) $(CompileParms) Range.cpp

Sheet.o:  Sheet.cpp
	$(CC) $(CompileParms) Sheet.cpp

SheetView.o:  SheetView.cpp
	$(CC) $(CompileParms) SheetView.cpp

main.o: main.cpp
	$(CC) $(CompileParms)  main.cpp

clean:
	rm *.o
