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

	//replaces a cell with value int
	void replaceCell(int index, int value);

	//replaces a cell with value string
	void replaceCell(int index, string value);

	//gets cell from vector at col index
	Cell* getCell(int index);

	//returns the begin of the col cell
	Cell* begin();

	//returns the end of the col cell
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

	//replaces cell at virtual coords x and y with value int
	void replaceCell(int x, int y, int value);

	//replaces a cell at virtual coords x and y with value string
	void replaceCell(int x, int y, string value);

	//gets a cell at coords x and y
	Cell* getCell(int x, int y);

	//gets a cell at coords char a and int y
	//WARNING: relative coords A1 correspond to "(0, 0)"
	Cell* getCell(char a, int y);

	//TODO: move to class Range
	Cell* begin(int column);

	//TODO: move to class Range
	Cell* end(int column);

	void print();
};

#endif