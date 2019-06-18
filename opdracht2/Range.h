
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <stdlib.h>

#ifndef RangeHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define RangeHVar  // wordt ge-include

using namespace std;

//This is the base class with basefunctions 
//for the stored values in the program.
struct CellValueBase
{
	CellValueBase() {};
public:
    //gives a stringstream with the
    //value in the stringstream
    //is empty if it's null
	virtual std::stringstream print();

    //returns typename T as type
	virtual std::string givetid();

    //returns the value as float
    //is -1 when it's null
	virtual float convertfloat();
};

//This class extends to types from the basefunctions
//for the typings int, string and float with templates.
template<typename T>
class CellValue : public CellValueBase
{
private:
    //initial value
	T value;
public:
    //constructor
	CellValue(T init);

    //returns the value in
    //type T
	T formvalue();

    //gives stringstream with value
	std::stringstream print(void);

    //gives typename T in string
	std::string givetid();

	//returns the value into a float
	virtual float convertfloat();

};



//Cell is the pointerclass to any CellValueBase and it's extensions.
//This is such that we can give different celltypes.
class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
public:
	//constructor
	Cell();

	void initCell(string value);

	//initializes a new cell with an integer value init
	void initCelli(int init);

	//initializes a new cell with string value init
	void initCelli(string init);

	void initCelli(float init);

	string givetype();

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};


//This class is for formulas, it stores both a 
//string and float in order to edit the string,
//but keep the float value intact.
class CellFormula : public Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
	string origin;
public:
	//constructor
	CellFormula(float value, string origin);

	void initCell(float value, string origin);

	//initializes a new cell with an integer value init
	void initCelli(int init);

	//initializes a new cell with string value init
	void initCelli(string init);

	void initCelli(float init);

	string givetype();

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};

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
	void replaceCell(int index, string value);
	
	//replaces a cell with value float
	void replaceCell(int index, float value);

	void replaceCell(int index, float value, string origin);

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

	//resize matrix to new size h and b
	void resize(int newh, int newb);

	//try to make the string into float first, then int
	//if that doesn't work, then check if the cell is a formula
	//otherwise just make a stringcell
	void parseCell(int x, int y, string value);

	//replaces cell at virtual coords x and y with value int
	void replaceCell(int x, int y, int value);

	//replaces a cell at virtual coords x and y with value string
	void replaceCell(int x, int y, string value);

	//replaces a cell at virtual coords x and y with value float
	void replaceCell(int x, int y, float value);

	void replaceCell(int x, int y, float value, string origin);

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


//This class is relevant for formulas
//it keeps track of the two coordinates that are inbetween the values
class CellAddress
{
private:
	int x, y;
public:
	//constructor
	CellAddress();

	//initializes values x and y corresponding
	//with coordinates in the sheet
	void init(int x, int y);

	//initializes values x and y corresponding
	//with coordinates in the sheet
	//but takes input as string: <column><row>
	void init(std::string input);

	//returns the coordinates in a int[2]
	int* givecoords();

	//returns the x-coordinate
	int givex();

	//returns the y-coordinate
	int givey();

	//adds another celladress to the current one
	CellAddress* operator +=(CellAddress &a);

	//adds another coordinate(s) to the current one
	CellAddress* operator +=(int coords[2]);

};

//*****************************************
//Range

//This class adds the formula functionality (SUM, AVG and COUNT)
//to the existing sheet class
class Range
{
private:
	Sheet* matrix;
	CellAddress begin;
	CellAddress end;
public:
	Range() {};

	//input is a pointer matrix
	//the pointer matrix needs to be
	//initialized first
	void initm(Sheet* matrix);

	//initializes new cell on coords (x, y) with proper value
	//according to either int, float, string or formula
	void initCell(int x, int y, string value);

	void resize(int newx, int newy);

	//sets beginning celladress to corresponding coords
	void setbegin(string input);

	//sets endadress to corresponding coords
	void setend(string input);

	//returns the original cell*
	//in location (x, y)
	Cell* getCell(int x, int y);

	//returns the original cell*
	//in location (a, col)
	Cell* getCell(char a, int col);

	//gives top left and bottom right
	//cells to compute sum
	void giveRows(string input);

	//sum method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	float iterRows(string input, Sheet* matrix);

	//count method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	unsigned int countcells(string input, Sheet* matrix);

	//avg method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	float averageCells(string input, Sheet* matrix);
};

class SheetObserver
{
private:
Range r;


};



#endif


