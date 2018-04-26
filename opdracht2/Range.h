
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

	//returns the coordinates of celladdress begin
	int* givebegincoords();

	//returns the coordinates of celladdress end
	int* giveendcoords();

	//prints the matrix in a cout
	void print();

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
	string iterRows(string input, Sheet* matrix);

<<<<<<< HEAD
	string countcells(string input, Sheet* matrix);

	string averageCells(string input, Sheet* matrix);
=======
	//count method of =METHOD(<coords1>:<coords2>)
	//used in the cells themselves to call a formula
	stringstream Count(string input);
>>>>>>> bf8e8c7c689c43396c0bee4cd61ca47372ff14b8
};

#endif
