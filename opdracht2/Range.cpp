#include "Range.h"
#include <string>
#include <iostream>

//*****************************************************
//CellAddrress

CellAddress::CellAddress()
{
	this->x = 0;
	this->y = 0;
};

//constructor
void CellAddress::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

//constructor
void CellAddress::init(std::string input)
{
	int i = 0;
	int size = input.size();
	if (size > 0)
	{
		this->x = 0;
		this->y = 0;
		while (!isdigit(input[i])){
			this->x = (this->x) * 26 + input[i] - 'A' + 1;
			i++;
		}
		for (; i < size; i++) {
			if (isdigit(input[i])){
				this->y = this->y * 10 + input[i] - '0';
			}
		}
	}
	this->x -= 1;
	this->y -= 1;
}

// returns coords in array
int* CellAddress::givecoords()
{
	return new int[2]{ x, y };
}

//returns x coord
int CellAddress::givex()
{
	return x;
}

//returns y coord
int CellAddress::givey()
{
	return y;
}

//operator += for another Celladdress object
CellAddress* CellAddress::operator +=(CellAddress &a)
{
	int* coords = a.givecoords();
	this->x += coords[0];
	this->y += coords[1];
	return this;
}

//operator += for another array object
CellAddress* CellAddress::operator +=(int coords[2])
{
	this->x += coords[0];
	this->y += coords[1];
	return this;
}


//*****************************************************
//Range

//constructor
void Range::initm(Sheet* matrix)
{
	this->matrix = matrix;
	begin = CellAddress();
	end = CellAddress();
}

//initializes a new cell, but filters the string
//such that formulas, int, float and string
//get the correct cell types
void Range::initCell(int x, int y, string value)
{
	int stringsize = value.size(), temp;

	//try formula
	try
	{
		string startparser = "", arg = "";
		float result = 0;
		int state = 0;
		
		if (value[0] == '=')
		{
			for(int i = 1; i < stringsize; i++)
			{
				if(value[i] == '(' && state == 0)
				{
					state = 1;
				}
				else if (state == 0)
				{
					startparser += value[i];
				}
				else if (state == 1 && value[i] == ')')
				{
					state = 2;
				}
				else if (state == 1)
				{
					arg += value[i];
				}
			}

			if(startparser == "SUM")
			{
				result = iterRows(arg, matrix);
			} 
			else if(startparser == "COUNT")
			{
				result = countcells(arg, matrix);
			}
			else if (startparser == "AVG")
			{
				result = averageCells(arg, matrix);
			}
			else
			{
				//otherwise it's a string
				throw 0;
			}
		}
		else
		{
			//otherwise it's a string
			throw 0;
		}
		matrix->replaceCell(x, y, result, value);
	}
	catch (int e)
	{
		try
		{
			if(stringsize < 8)
			{
				temp = atof(value.c_str());
				matrix->replaceCell(x, y, temp, value);
			}

		}
		catch (int i)
		{
			try
			{
				if(stringsize < 11)
				{
					temp = atoi(value.c_str());
					matrix->replaceCell(x, y, temp, value);
				}

			}
			catch(const std::exception& e)
			{
				matrix->replaceCell(x, y, value, value);
			}
		}
	}	
}

//resizes the matrix to new size
//newx by newy
void Range::resize(int newx, int newy)
{
	matrix->resize(newx, newy);
}

//sets startingcell of the range
//needed for the formula
void Range::setbegin(string input)
{
	begin.init(input);
}

//sets endingcell of the range
//needed for the formula
void Range::setend(string input)
{
	end.init(input);
}

//returns cellpointer at coords (x, y)
Cell* Range::getCell(int x, int y)
{
	if(x >= 0 && y >= 0)
	{
		return matrix->getCell(x, y);
	}
	return new Cell();
}

//returns cellpointer at coords (a, col)
//note: (A, 1) = (0, 0)
Cell* Range::getCell(char a, int col)
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
float Range::iterRows(string input, Sheet* matrix)
{
	float temp = 0;
	string str;
    giveRows(input);

    for(int i = begin.givex(); i <= end.givex(); i++)
    {
        for(int j = begin.givey(); j <= end.givey(); j++)
        {
					string str = matrix->getCell(i, j)->giveref()->print().str();
					try {temp += atof(str.c_str());}
					catch(exception e){return 0;}
        }
    }
    return temp;
}

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
//does COUNT
unsigned int Range::countcells(string input, Sheet* matrix)
{
	unsigned int h, temp = 0;
	bool containsno;
	string str;

	giveRows(input);

	for(int i = begin.givex(); i <= end.givex(); i++)
	{
		for(int j = begin.givey(); j <= end.givey(); j++)
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
	return temp;
}

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
//does AVG
float Range::averageCells(string input, Sheet* matrix)
{
	float temp = 0, temp2 = 0;
	int counter = 0;
	string str;
  	giveRows(input);
	  
  for(int i = begin.givex(); i <= end.givex(); i++)
  {
    for(int j = begin.givey(); j <= end.givey(); j++)
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
  return (temp2/counter);
}
