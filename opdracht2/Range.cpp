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


