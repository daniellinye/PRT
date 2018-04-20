
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

	void initm(Sheet* matrix);

	void setbegin(int x, int y);

	void setend(int x, int y);

	void print();

	Cell* getCell(int x, int y);

	Cell* getCell(char a, int col);

	Cell** giveRows(string input);
};

#endif