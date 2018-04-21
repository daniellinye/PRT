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

void Range::setbegin(string input)
{
	begin = CellAddress();
	begin.init(input);
}

void Range::setend(string input)
{
	end = CellAddress();
	end.init(input);
}

int* Range::givebegincoords()
{
	return begin.givecoords();
}

int* Range::giveendcoords()
{
	return end.givecoords();
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
	return matrix->getCell(a, col);
}

void Range::giveRows(string input)
{
	string leftn = "", rightn = "";
	int i = 0, arsize = sizeof(input);
	bool passed = false;
	
	//parse the string
	while(i < arsize)
	{
		if(passed)
		{
			rightn += input[i];
		}
		else if(input[i] != ':')
		{
			passed = true;
		}
		else
		{
			leftn += input[i];
		}
		i++;
	}
	begin.init(leftn);
	end.init(rightn);
}

//actually is SUM
stringstream Range::iterRows(string input)
{
	stringstream ss;
	giveRows(input);

	int *begin = givebegincoords(), *end = giveendcoords();

	for(int i = begin[0]; i <= end[0]; i++)
	{
		for(int j = begin[1]; j <= end[1]; j++)
		{
			ss << getCell(i, j)->giveref()->print().str();
		}
	}
	return ss;
}



