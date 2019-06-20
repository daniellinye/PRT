
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include "Sheet.h"
#include "CellAddress.h"

#ifndef RangeHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define RangeHVar  // wordt ge-include


//*****************************************
//Range

//This class adds the formula functionality (SUM, AVG and COUNT)
//to the existing sheet class
class Range
{
private:
	CellAddress begin;
	CellAddress end;
public:
	Range() {};

	void resize(Sheet* matrix, int newx, int newy);

	//sets beginning celladress to corresponding coords
	void setbegin(std::string input);

	//sets endadress to corresponding coords
	void setend(std::string input);

	//returns the original cell*
	//in location (x, y)
	Cell* getCell(Sheet* matrix, int x, int y);

	//returns the original cell*
	//in location (a, col)
	Cell* getCell(Sheet* matrix, char a, int col);

	//gives top left and bottom right
	//cells to compute sum
	void giveRows(Sheet* matrix, std::string input);

	//sum method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	float iterRows(Sheet* matrix, std::string input);

	//count method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	unsigned int countcells(Sheet* matrix, std::string input);

	//avg method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	float averageCells(Sheet* matrix, std::string input);
};

class SheetObserver
{
private:
Range r;


};



#endif


