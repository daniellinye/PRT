
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

	int* givebegincoords();
	
	int* giveendcoords();

	void print();

	Cell* getCell(int x, int y);

	Cell* getCell(char a, int col);

	//gives top left and bottom right
	//cells to compute sum
	void giveRows(string input);


	stringstream iterRows(string input);
};

#endif