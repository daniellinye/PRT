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

void Range::initCell(int x, int y, string value)
{
		//try int conversion
	try
	{
		int temp = atoi(value.c_str());
		matrix->replaceCell(x, y, temp);

	}
	catch(exception)
	{
		//try float conversion
		try
		{
			float temp = atoi(value.c_str());
			matrix->replaceCell(x, y, temp);
		}
		catch(exception)
		{
			//try formula
			try
			{
				string sum("SUM(");      //in every if-statement
				string count("COUNT(");  // - gets checked whether it begins -and ends with the propper syntax
				string avg("AVG(");      // - a substring of the coordinates gets extracted
				string substring;        // - the corresponding function gets called
				unsigned begin;
				unsigned end = value.find(')');
				if (value[0] == '=')
				{
					if ((value.find(sum) != string::npos) && value.back() == ')') {
						begin = value.find(sum);
						substring = value.substr(begin + sum.length(),end - begin - sum.length());
						value = iterRows(substring, matrix);
					}
					else if ((value.find(count) != string::npos) && value.back() == ')') {
						begin = value.find(count);
						substring = value.substr(begin + count.length(),end - begin - count.length());
						value = countcells(substring, matrix);
					}
					else if ((value.find(avg) != string::npos) && value.back() == ')') {
						begin = value.find(avg);
						substring = value.substr(begin + avg.length(),end - begin - avg.length());
						value = averageCells(substring, matrix);
					}
				}
				else
				{
					throw 0;
				}
			}
			catch (int e)
			{
				matrix->replaceCell(x, y, value);
			}
		}
	}
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

//returns cellpointer at coords (x, y)
Cell* Range::getCell(int x, int y)
{
	return matrix->getCell(x, y);
}

//returns cellpointer at coords (a, col)
Cell* Range::getCell(char a, int col)
{
	return matrix->getCell(a, col);
}

//gives both celladdresses in the function
//the proper coordinates before using the
//looping the rows
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
  return (temp2/counter);
}
