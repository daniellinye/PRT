#include "Range.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>


//*****************************************************
//Range

//resizes the matrix to new size
//newx by newy
void Range::resize(Sheet* matrix, int newx, int newy)
{
	matrix->resize(newx, newy);
}

//sets startingcell of the range
//needed for the formula
void Range::setbegin(std::string input)
{
	begin.init(input);
	//check if they need to be swapped
	if(begin.givex() < end.givex() || 
	(begin.givex() == end.givex() && begin.givey() < end.givey()))
	{
		begin.init(end.givex(), end.givey());
		end.init(input);
	}
}

//sets endingcell of the range
//needed for the formula
void Range::setend(std::string input)
{
	end.init(input);
	//check if they need to be swapped
	if(begin.givex() < end.givex()  || 
	(begin.givex() == end.givex() && begin.givey() < end.givey()))
	{
		begin.init(end.givex(), end.givey());
		end.init(input);
	}
}

//returns cellpointer at coords (x, y)
Cell* Range::getCell(Sheet* matrix, int x, int y)
{
	if(x >= 0 && y >= 0)
	{
		return matrix->getCell(x, y);
	}
	return new Cell();
}

//returns cellpointer at coords (a, col)
//note: (A, 1) = (0, 0)
Cell* Range::getCell(Sheet* matrix, char a, int col)
{
	if(a >= 'A' && a <= 'Z' && col > 0)
	{
		return matrix->getCell(a, col);
	}
	return new Cell();
}

//gives both celladdresses in the function
//the proper coordinates before using the
//looping the rows
//<location a>:<location b> as string
void Range::giveRows(Sheet* matrix, std::string input)
{
	std::string leftn = "", rightn = "";
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
float Range::iterRows(Sheet* matrix, std::string input)
{
	float temp = 0;
	std::string str;
    giveRows(matrix, input);

    int beginx = begin.givex(), beginy = begin.givey(),
		endy = end.givey(), endx = end.givex();

    for(int i = beginx; i <= endx; i++)
    {
        for(int j = beginy; j <= endy; j++)
        {
					std::string str = matrix->getCell(i, j)->giveref()->print().str();
					try {temp += atof(str.c_str());}
					catch(std::exception e){return 0;}
        }
    }
    return temp;
}

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
//does COUNT
unsigned int Range::countcells(Sheet* matrix, std::string input)
{
	unsigned int h, temp = 0;
	bool containsno;
	std::string str;

	giveRows(matrix, input);
	int beginx = begin.givex(), beginy = begin.givey(),
	endy = end.givey(), endx = end.givex();

	for(int i = beginx; i <= endx; i++)
	{
		for(int j = beginy; j <= endy; j++)
	  {
			containsno = false;
			std::string str = matrix->getCell(i, j)->giveref()->print().str();
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
	return temp;
}

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
//does AVG
float Range::averageCells(Sheet* matrix, std::string input)
{
	float temp = 0, temp2 = 0;
	int counter = 0;
	std::string str;
  	giveRows(matrix, input);
	int beginx = begin.givex(), beginy = begin.givey(),
	endy = end.givey(), endx = end.givex();

  for(int i = beginx; i <= endx; i++)
  {
    for(int j = beginy; j <= endy; j++)
    {
			std::string str = matrix->getCell(i, j)->giveref()->print().str();
			temp = matrix->getCell(i, j)->giveref()->convertfloat();
			try {
				temp2 += atof(str.c_str());
				if (str == "0" || temp != 0) {counter++;}
			}
			catch(std::exception e){return 0;}
    }
  }
  return (temp2/counter);
}

