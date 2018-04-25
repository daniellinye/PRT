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

void Range::giveRows(string input)
{
	string leftn = "", rightn = "";
	int i = 0, arsize = input.size();
	bool passed = false;

	//parse the string
	while(i < arsize)
	{
		if(passed)
		{
			rightn += input[i];
		}
		else if(input[i] == ':')
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

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
string Range::iterRows(string input, Sheet* matrix)
{
		int temp = 0;
		string str;
    giveRows(input);

    int beginx = begin.givex(), beginy = begin.givey(),
		endy = end.givey(), endx = end.givex();

    for(int i = beginx; i <= endx; i++)
    {
        for(int j = beginy; j <= endy; j++)
        {
					string str = matrix->getCell(i, j)->giveref()->print().str();
					try {temp += atoi(str.c_str());}
					catch(exception e){return 0;}
        }
    }
    return (string) temp;
}
