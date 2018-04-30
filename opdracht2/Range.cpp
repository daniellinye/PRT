#include "Range.h"

void Range::initm(Sheet* matrix)
{
	this->matrix = matrix;
	begin = CellAddress();
	end = CellAddress();
}

//sets startingcell of the range
void Range::setbegin(string input)
{
	begin.init(input);
}

//sets endingcell of the range
void Range::setend(string input)
{
	end.init(input);
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
//does SUM
string Range::iterRows(string input, Sheet* matrix)
{
	float temp = 0;
	string str;
    giveRows(input);

    int beginx = begin.givex(), beginy = begin.givey(),
		endy = end.givey(), endx = end.givex();

    for(int i = beginx; i <= endx; i++)
    {
        for(int j = beginy; j <= endy; j++)
        {
					string str = matrix->getCell(i, j)->giveref()->print().str();
					try {temp += atof(str.c_str());}
					catch(exception e){return 0;}
        }
    }
    return to_string(temp);
}

string Range::countcells(string input, Sheet* matrix)
{
	unsigned int h, temp = 0;
	bool containsno;
	string str;

	giveRows(input);
	int beginx = begin.givex(), beginy = begin.givey(),
	endy = end.givey(), endx = end.givex();

	for(int i = beginx; i <= endx; i++)
	{
		for(int j = beginy; j <= endy; j++)
	  {
			containsno = false;
			string str = matrix->getCell(i, j)->giveref()->print().str();
			for (h = 0; h < str.size(); h++) {
				if (isdigit(str[h])) {
					containsno = true;
				}
			}
			if (containsno) {
				temp++;
			}
	  }
	}
	return to_string(temp);
}

string Range::averageCells(string input, Sheet* matrix)
{
	float temp = 0, temp2 = 0;
	int counter = 0;
	string str;
  giveRows(input);

  int beginx = begin.givex(), beginy = begin.givey(),
	endy = end.givey(), endx = end.givex();

  for(int i = beginx; i <= endx; i++)
  {
    for(int j = beginy; j <= endy; j++)
    {
			string str = matrix->getCell(i, j)->giveref()->print().str();
			temp = matrix->getCell(i, j)->giveref()->convertfloat();
			try {
				temp2 += atof(str.c_str());
				if (str == "0" || temp != 0) {counter++;}
			}
			catch(exception e){return 0;}
    }
  }
  return to_string(temp2/counter);
}
