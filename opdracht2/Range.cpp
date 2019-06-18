#include "Range.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;


//*****************************************************
//CellValueBase
//Baseclass for all Cell values

std::stringstream CellValueBase::print()
{
	std::stringstream ss;
	ss << "";
	return ss;
}

//returns typename T as type
std::string CellValueBase::givetid()
{
	return "nonetype";
}

//returns the value as float
//is -1 when it's null
float CellValueBase::convertfloat()
{
	return -1;
}

//*****************************************************
//CellValue
//Generic constructor that carries multiple typenames

//constructor
template <typename T>
CellValue<T>::CellValue(T init) : CellValueBase()
{
	this->value = init;
}

//returns stringstream with value in cell<float>
template <>
std::stringstream CellValue<float>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

//returns stringstream with value in cell<int>
template <>
std::stringstream CellValue<int>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

//returns stringstream with value in cell<string>
template <>
std::stringstream CellValue<string>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

template<>
std::string CellValue<int>::givetid()
{
	return "int";
}

template<>
std::string CellValue<float>::givetid()
{
	return "float";
}

template<>
std::string CellValue<string>::givetid()
{
	return "string";
}

//returns the value into a float
template<>
float CellValue<int>::convertfloat()
{
	return (float) value;
}

//returns the value into a float
template<>
float CellValue<string>::convertfloat()
{
	float temp = 0;
	bool decimal = false;
	int i, n = 0;
	for (char chars : value)
	{
		if (chars == '.' || chars == ',') {
			decimal = true;
		}
		else if (chars >= '0' && chars <= '9') {
			temp = temp * 10 + (chars - '0');
			if (decimal) {
				n++;
			}
		}
	}
	if (decimal) {
		for (i = 0; i < n; i++) {
			temp /= 10;
		}
	}
	return temp;
}

//returns the value into a float
template<>
float CellValue<float>::convertfloat()
{
	return value;
}

//*****************************************************
//Cell
//Pointerclass to CellValues

//constructor
Cell::Cell()
{
	value.reset(nullptr);
	value = unique_ptr<CellValueBase>(new CellValue<string>(""));
}


//filters cells to proper value and initializes them
void Cell::initCell(string value)
{
	bool isint = true, isfloat = true;
	int temp;
	float temp2;

	for(char element : value)
	{
		if(element < '0' && element > '9')
		{
			isint = false;
			if(element != '.' && element != ',')
			{
				isfloat = false;
			}
		}
	}

	if(isint)
	{
		try
		{
			temp = atoi(value.c_str());
			initCelli(temp);
		}
		catch(int i)
		{
			cout << "rip" << endl;
		}
		
	}
	else if(isfloat)
	{
		try
		{
			temp2 = atof(value.c_str());
			initCelli(temp2);
		}
		catch(int i)
		{
			cout << "rip" << endl;
		}
	}
	else
	{
		initCelli(value);
	}
}

//inits the cell with an int
void Cell::initCelli(int init)
{

	auto cvar = new CellValue<int>(init);
	delete &value;
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a string
void Cell::initCelli(string init)
{
	auto cvar = new CellValue<string>(init);
	delete &value;
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a float
void Cell::initCelli(float init)
{
	auto cvar = new CellValue<float>(init);
	delete &value;
	value = unique_ptr<CellValueBase>(cvar);
}

//returns the cellvaluebase reference pointer
CellValueBase* Cell::giveref()
{
	if (value != 0)
	{
		return value.get();
	}
	return NULL;
}

//*****************************************************
//CellFormula

CellFormula::CellFormula(float value, string origin)
{
	this->value.reset(nullptr);
	this->value = unique_ptr<CellValueBase>(new CellValue<string>(""));
	auto cvar = new CellValue<float>(value);
	this->value = unique_ptr<CellValueBase>(cvar);
	this->origin = origin;
}


//*****************************************************
//Column
//vector<Cell*> class

//constructor
Column::Column(int size)
{
	this->size = size;
	for(int i = 0; i < size; i++)
	{
		col.push_back(new Cell());
	}
}

//nested resize function in column
//saves complexity if written here
void Column::resize(int newsize)
{
	if(newsize > size)
	{
		for(int i = size; i < newsize; i++)
		{
			col.push_back(new Cell());
		}
	}
	else
	{
		for(int i = size; i > newsize; i--)
		{
			col.pop_back();
		}
	}
}

void Column::replaceCell(int index, int newvalue)
{
	col[index]->initCelli(newvalue);
}

void Column::replaceCell(int index, float newvalue)
{
	col[index]->initCelli(newvalue);
}

//replace existing cell with new value string
void Column::replaceCell(int index, string newvalue)
{
	col[index]->initCell(newvalue);
}

void Column::replaceCell(int index, float newvalue, string origin)
{
	delete col[index];
	col[index] = new CellFormula(newvalue, origin);
}

//get cellpointer from index
Cell* Column::getCell(int index)
{
	return col[index];
}

//get first cell in the vector
Cell* Column::begin()
{
	if(col.size() > 0)
		return col[0];
	else
		return new Cell();
}

//get last cell in the vector
Cell* Column::end()
{
	if(col.size() > 0)
		return col[col.size() - 1];
	else
		return new Cell();
}


//*****************************************************
//Sheet
//Vector<Column> class

//constructor
Sheet::Sheet(int h, int b)
{
	this->h = h;
	this->b = b;
	//fill matrix with h x b cells that are empty
	for(int i = 0; i < b; i++)
	{
		matrix.push_back(Column(h));
	}
}

//resizes the matrix
void Sheet::resize(int newh, int newb)
{
	//check wether the sizes are valid
	if(newh > 0 && newb > 0)
	{
		//in case the matrix has to become larger, make new vector elements
		if(newb > b)
		{
			for(int i = 0; i < b; i++)
			{
				matrix[i].resize(newh);
			}
			for(int i = b; i < newb; i++)
			{
				matrix.push_back(Column(newh));
			}
		}
		else
		{
			//otherwise only remove vector elements and handle the rest with
			//mested function in column
			for(int i = b; i > newb; i--)
			{
				matrix.pop_back();
			}
			for(int i = 0; i < newb; i++)
			{
				matrix[i].resize(newh);
			}
		}
		this->h = newh;
		this->b = newb;
	}
}

//replaces cell with new value string
void Sheet::replaceCell(int x, int y, string value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

//replaces cell with new value int
void Sheet::replaceCell(int x, int y, int value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

//replaces cell with new value float
void Sheet::replaceCell(int x, int y, float value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

void Sheet::replaceCell(int x, int y, float value, string origin)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value, origin);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

//get a cell in the matrix at coords (x, y)
Cell* Sheet::getCell(int x, int y)
{
	if(x < b && y < h && x > -1 && y > -1)
		return matrix[x].getCell(y);
	else
		return new Cell();
}

//get a cell in the matrix at coords (a - 'A', y - 1)
Cell* Sheet::getCell(char a, int y)
{
	if (a >= 'A' && a <= 'Z' && y < h + 1 && y > -1)
		return matrix[a - 'A'].getCell(y - 1);
	else
		return new Cell();
}




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
	//first see if it's a formula
	try
	{
		string startparser = "", arg = "";
		float result = 0;
		int state = 0;
		if (value[0] == '=')
		{
			for(char val : value)
			{
				if(val == '(' && state == 0)
				{
					state = 1;
				}
				else if (state == 0)
				{
					startparser += val;
				}
				else if (state == 1 && val == ')')
				{
					state = 2;
				}
				else if (state == 1)
				{
					arg += val;
				}
			}//for

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
			matrix->replaceCell(x, y, result, value);
				
		}//if val[0] = '='
		else
		{
			matrix->replaceCell(x, y, result);
		}
	}
	catch (int e)
	{
		cout << e << endl;
		matrix->replaceCell(x, y, value);
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

