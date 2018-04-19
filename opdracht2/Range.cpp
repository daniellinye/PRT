#include "Range.h"

/*
WATCH OUT:
CELL DECLARATION:
(1, A)
CORRESPONDS TO COORDINATES
(0, 0)
*/

void Range::initm(Sheet* matrix)
{
	this->matrix = matrix;
}

void Range::setbegin(int x, int y)
{
	begin = CellAddress();
	begin.init(x, y);
}

void Range::setend(int x, int y)
{
	end = CellAddress();
	end.init(x, y);
}

void Range::print()
{
	matrix->print();
}

Cell* Range::getCell(int x, int y)
{
	return matrix->getCell(x, y);
}

Cell* Range::getCell(char a, int col)
{
	
}

stringstream Range::giveRows(string input)
{
	char leftl = input[0], rightl; 
	string leftn = "", rightn = "";
	int i = 1, x1, x2;
	while(i < sizeof(input) && input[i] != ':')
	{
		leftn += input[i];
		i++;
	}
	x1 = stoi(leftn);
}


