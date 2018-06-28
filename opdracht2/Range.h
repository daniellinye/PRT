#include "Sheet.h"
#include <string>
#include <iostream>

#ifndef RangeHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define RangeHVar  // wordt ge-include

using namespace std;

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




#endif
