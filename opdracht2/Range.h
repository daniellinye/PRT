
#include "CellAddress.h"
#include "Sheet.h"

#ifndef RangeHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define RangeHVar  // wordt ge-include 

using namespace std;

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

	//sets beginning celladress to corresponding coords
	void setbegin(string input);

	//sets endadress to corresponding coords
	void setend(string input);

	//returns in a int[2] the coordinates of the
	//start of the formula
	int* givebegincoords();
	
	//returns in a int[2] the coordinates of the
	//end of the formula
	int* giveendcoords();

	//prints everything
	void print();

	//returns the location of the original cell
	//at location (x, y)
	Cell* getCell(int x, int y);

	//returns the location of the original cell
	//at location (<row>, <column>)
	//ex: (A, 4)
	Cell* getCell(char a, int col);

	//gives top left and bottom right
	//cells to compute sum
	void giveRows(string input);

	//takes input
	//<location a>:<location b> as string
	//and converts it into a stringstream
	stringstream iterRows(string input);
};

#endif