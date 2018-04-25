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
	begin = CellAddress();
	end = CellAddress();
}

void Range::replaceCell(int x, int y, string input)
{
	stringstream ss;
	if(input[0] == '=')
	{
		ss = iterRows(input, x, y);
	}
	matrix->replaceCell(x, y, input, ss);

}

void Range::replaceCell(int x, int y, int input)
{
	matrix->replaceCell(x, y, input);
}

void Range::setbegin(string input)
{

	begin.init(input);
}

void Range::setend(string input)
{

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

void Range::castFormula(string input)
{
	string leftn = "", rightn = "";
	int i = 1, arsize = sizeof(input);
	bool passed = false;
	while(i < arsize)
	{
		if(passed)
		{
			rightn += input[i];
		}
		else if(input[i] != '(')
		{
			passed = true;
		}
		else
		{
			leftn += input[i];
		}
		i++;
	}
	cout << left << rightn;
	giveRows(rightn);
}

void Range::giveRows(string input)
{
	string leftn = "", rightn = "";
	int i = 0, arsize = sizeof(input);
	bool passed = false;
	
	//parse the string
	while(i < arsize && input[i] != ')')
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
	//TODO:fix both these lines
	setbegin(leftn);
	setend(rightn);
}

//iters ranges and gives the stringstream back with values
stringstream Range::iterRows(string input, int x, int y)
{
	stringstream ss;
	castFormula(input);

	int *begin = givebegincoords(), *end = giveendcoords();

	for(int i = begin[0]; i <= end[0]; i++)
	{
		for(int j = begin[1]; j <= end[1]; j++)
		{
			//TODO: FIX THIS LINE
			cout << getCell(i, j)->giveref()->print().str() << endl;
		}
	}
	return ss;
}



