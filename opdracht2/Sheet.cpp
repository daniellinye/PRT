#include "Sheet.h"
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

//*****************************************************
//CellValueBase

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

//constructor
template <typename T>
CellValue<T>::CellValue(T init) : CellValueBase()
{
	this->value = init;
}

//returns value in cell
template <typename T>
T CellValue<T>::formvalue()
{
	return value;
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

//returns typename of cell
template <typename T>
std::string CellValue<T>::givetid()
{
	return typeid(T).name();
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

//constructor
Cell::Cell()
{
	value.reset(nullptr);
	value = unique_ptr<CellValueBase>(new CellValue<string>(""));
}

//inits the cell with an int
void Cell::initCelli(int init)
{

	auto cvar = new CellValue<int>(init);
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a string
void Cell::initCelli(string init)
{
	auto cvar = new CellValue<string>(init);
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a float
void Cell::initCelli(float init)
{
	auto cvar = new CellValue<float>(init);
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
//Column

Column::Column(int size)
{
	this->size = size;
	for(int i = 0; i < size; i++)
	{
		col.push_back(new Cell());
	}
}

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

void Column::replaceCell(int index, string newvalue)
{
	col[index]->initCelli(newvalue);
}

void Column::replaceCell(int index, float newvalue)
{
	col[index]->initCelli(newvalue);
}

Cell* Column::getCell(int index)
{
	return col[index];
}

Cell* Column::begin()
{
	if(col.size() > 0)
		return col[0];
	else
		return new Cell();
}

Cell* Column::end()
{
	if(col.size() > 0)
		return col[col.size() - 1];
	else
		return new Cell();
}


//*****************************************************
//Sheet

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

void Sheet::resize(int newh, int newb)
{
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

//replaces cell with new value
void Sheet::replaceCell(int x, int y, string value)
{
	if(x < b && y < h)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

void Sheet::replaceCell(int x, int y, int value)
{
	if(x < b && y < h)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

void Sheet::replaceCell(int x, int y, float value)
{
	if(x < b && y < h)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

Cell* Sheet::getCell(int x, int y)
{
	if(x < b && y < h)
	return matrix[x].getCell(y);
	else
	return NULL;
}

Cell* Sheet::getCell(char a, int y)
{
	if (a >= 'A' && a <= 'Z')
		return matrix[a - 'A'].getCell(y - 1);
	else
		return NULL;
}
