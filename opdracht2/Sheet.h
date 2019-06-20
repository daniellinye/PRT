#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Cell.h"

#ifndef SheetHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define SheetHVar  // wordt ge-include

//Matrix has columns, 
//this is such that we can edit on a lower level.
//Column has a row of cells, which can be resized or replaced.
class Column
{
private:
	std::vector<Cell*> col;
	int size;
public:
	Column(int size);

	//resize vectorcolumns to proper size
	void resize(int newsize);

	//replaces a cell with value int
	void replaceCell(int index, int value);

	//replaces a cell with value string
	void replaceCell(int index, std::string value);
	
	//replaces a cell with value float
	void replaceCell(int index, float value);

	void replaceCell(int index, float value, std::string origin);

	//gets cell from vector at col index
	Cell* getCell(int index);

	//returns the begin of the col cell
	Cell* begin();

	//returns the end of the col cell
	Cell* end();

};


//Sheet is a class with Columns
//it essentially is a matrix class with functions
//it can replace, get cells or resize
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

	//initializes new cell on coords (x, y) with proper value
	//according to either int, float, string or formula
	void initCell(int x, int y, std::string value);

	//resize matrix to new size h and b
	void resize(int newh, int newb);

	//try to make the string into float first, then int
	//if that doesn't work, then check if the cell is a formula
	//otherwise just make a stringcell
	void parseCell(int x, int y, std::string value);

	//replaces cell at virtual coords x and y with value int
	void replaceCell(int x, int y, int value);

	//replaces a cell at virtual coords x and y with value string
	void replaceCell(int x, int y, std::string value);

	//replaces a cell at virtual coords x and y with value float
	void replaceCell(int x, int y, float value);

	void replaceCell(int x, int y, float value, std::string origin);

	//gets a cell at coords x and y
	Cell* getCell(int x, int y);

	//gets a cell at coords char a and int y
	//Note: relative coords A1 correspond to "(0, 0)"
	Cell* getCell(char a, int y);

	//returns the begin of a cell in a column
	Cell* begin(int column);

	//returns the end of a cell in a column
	Cell* end(int column);
};

#endif