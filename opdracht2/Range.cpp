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
void CellAddress::givecoords(int &x, int &y)
{
	x = this->x;
	y = this->y;
}

//operator += for another Celladdress object
CellAddress* CellAddress::operator +=(CellAddress &a)
{
	int x,y;
	a.givecoords(x,y);
	this->x += x;
	this->y += y;
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
	int stringsize = value.size(), temp, isfloat = 0, state = 0;
	bool isint = true;
	string startparser = "", arg = "";
	float result = 0;

	//first parse the cels
	for(int i = 0; i < stringsize; i++)
	{
		if(value[i] < '0' && value[i] > '9')
		{
			isint = false;
			if(value[i] == '.')
			{
				isfloat++;
			}
		}
	}

	try
	{
		//then try formula
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
			matrix->replaceCell(x,y,result, value);
			return;
		}
		else
		{
			//otherwise it's a string
			throw 0;
		}

	}
	catch (int e)
	{
		//then add
		try
		{
			if(stringsize < 8 && isint)
			{
				temp = atof(value.c_str());
				matrix->replaceCell(x, y, temp, value);
			}
		}
		catch (int i)
		{
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
					matrix->replaceCell(x,y,result, value);
					return;
				}
				else
				{
					temp = atoi(value.c_str());
					matrix->replaceCell(x, y, temp, value);
					return;
				}

			}
			catch(const std::exception& e)
			{
				matrix->replaceCell(x, y, value, value);
				return;
			}
		}
	}
	matrix->replaceCell(x, y, value, value);
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
	return NULL;
}

//returns cellpointer at coords (a, col)
//note: (A, 1) = (0, 0)
Cell* Range::getCell(char a, int col)
{
	if(a >= 'A' && a <= 'Z' && col > 0)
	{
		return matrix->getCell(a, col);
	}
	return NULL;
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
	int beginx,beginy,endx,endy;
	float temp = 0;
	string str;
  giveRows(input);

	begin.givecoords(beginx,beginy);
	end.givecoords(endx,endy);

  for(int i = beginx; i <= endx; i++)
  {
    for(int j = beginy; j <= endy; j++)
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
	int beginx,beginy,endx,endy;
	bool containsno;
	string str;

	giveRows(input);

	begin.givecoords(beginx,beginy);
	end.givecoords(endx,endy);

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
	return temp;
}

//takes input
//<location a>:<location b> as string
//and converts it into a stringstream
//does AVG
float Range::averageCells(string input, Sheet* matrix)
{
	float temp = 0, temp2 = 0;
	int beginx,beginy,endx,endy;
	int counter = 0;
	string str;
  giveRows(input);

	begin.givecoords(beginx,beginy);
	end.givecoords(endx,endy);

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
  return (temp2/counter);
}
