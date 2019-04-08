#include "Sheet.h"
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

template <typename T>
CellValue<T>::CellValue(T init, string memory) : CellValueBase()
{
	this->value = init;
	this->memory = memory;
}

template <typename T>
string CellValue<T>::returnmemory()
{
	return this->memory;
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
//Pointerclass to CellValues

//constructor
Cell::Cell()
{
	value.reset(nullptr);
	value = unique_ptr<CellValueBase>(new CellValue<string>(""));
}

//inits the cell with an int
void Cell::initCelli(int init, string mem)
{

	auto cvar = new CellValue<int>(init, mem);
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a string
void Cell::initCelli(string init, string mem)
{
	auto cvar = new CellValue<string>(init, mem);
	value = unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a float
void Cell::initCelli(float init, string mem)
{
	auto cvar = new CellValue<float>(init, mem);
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

//replace existing cell with new value int
void Column::replaceCell(int index, int newvalue, string mem)
{
	col[index]->initCelli(newvalue, mem);
}

//replace existing cell with new value string
void Column::replaceCell(int index, string newvalue, string mem)
{
	col[index]->initCelli(newvalue, mem);
}

//replace existing cell with new value float
void Column::replaceCell(int index, float newvalue, string mem)
{
	col[index]->initCelli(newvalue, mem);
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
void Sheet::replaceCell(int x, int y, string value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value, mem);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

//replaces cell with new value int
void Sheet::replaceCell(int x, int y, int value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value, mem);
	}
	else
	{
		cout << "Cell was not in scope of matrix" << endl;
	}
}

//replaces cell with new value float
void Sheet::replaceCell(int x, int y, float value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value, mem);
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
