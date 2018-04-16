#include "Cell.h"
#include <vector>
#include <memory>
#include <sstream>
#ifndef SheetHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define SheetHVar  // wordt ge-include 

using namespace std;


class Column
{
private:
	std::vector<Cell*> col;
	int size;
public:
	Column(int size);

	Cell* getCell(int index);
	Cell* begin();
	Cell* end();
};


//TODO: make new class so that class Column contains the columns of vector<Cell*>
class Sheet
{
private:
	std::vector<Column> matrix;
	//temporary empty cell
	int h, b;
public:
	//initializes the sheet with
	//height h and width b
	Sheet(int h, int b);

	//gets a cell from the 	
	Cell* getCell(int x, int y);


	Cell* getCell(char a, int y);

	//TODO: move to class Range
	Cell* begin(int column);

	//TODO: move to class Range
	Cell* end(int column);

	void print();
};

#endif