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
} // print

//returns typename T as type
std::string CellValueBase::givetid()
{
	return "nonetype";
} // givetid

//returns the value as float
//is -1 when it's null
float CellValueBase::convertfloat()
{
	return -1;
} // convertfloat

//*****************************************************
//CellValue
//Generic constructor that carries multiple typenames

//constructor
template <typename T>
CellValue<T>::CellValue(T init) : CellValueBase()
{
	this->value = init;
} // constructor

template <typename T>
CellValue<T>::CellValue(T init, string memory) : CellValueBase()
{
	this->value = init;
	this->memory = memory;
} // constructor

template <typename T>
string CellValue<T>::returnmemory()
{
	return this->memory;
} // returnmemory

//returns stringstream with value in cell<float>
template <>
std::stringstream CellValue<float>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
} // print<float>

//returns stringstream with value in cell<int>
template <>
std::stringstream CellValue<int>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
} // print<int>

//returns stringstream with value in cell<string>
template <>
std::stringstream CellValue<string>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
} // print<string>

//returns typename of cell
template <typename T>
std::string CellValue<T>::givetid()
{
	return typeid(T).name();
} // givetid

//returns the value into a float
template<>
float CellValue<int>::convertfloat()
{
	return (float) value;
} // convertfloat<int>

//returns the value into a float
template<>
float CellValue<string>::convertfloat()
{
	float temp = 0;
	bool decimal = false;
	int i, n = 0;

	for (char chars : value)
	{
		if (chars == '.' || chars == ',')
		{
			decimal = true;
		}

		else if (chars >= '0' && chars <= '9')
		{
			temp = temp * 10 + (chars - '0');
			if (decimal)
				n++;
		} // else if
	} // for

	if (decimal)
		for (i = 0; i < n; i++)
			temp /= 10;

	return temp;
} // convertfloat<string>

//returns the value into a float
template<>
float CellValue<float>::convertfloat()
{
	return value;
} // convertfloat<float>

//*****************************************************
//Cell
//Pointerclass to CellValues

//constructor
Cell::Cell()
{
	value.reset(nullptr);
	value = unique_ptr<CellValueBase>(new CellValue<string>(""));
} // constructor

//destructor
Cell::~Cell()
{

} // destructor

//inits the cell with an int
void Cell::initCelli(int init, string mem)
{
	auto cvar = new CellValue<int>(init, mem);
	value = unique_ptr<CellValueBase>(cvar);
} // initCelli

//inits the cell with a string
void Cell::initCelli(string init, string mem)
{
	auto cvar = new CellValue<string>(init, mem);
	value = unique_ptr<CellValueBase>(cvar);
} // initCelli

//inits the cell with a float
void Cell::initCelli(float init, string mem)
{
	auto cvar = new CellValue<float>(init, mem);
	value = unique_ptr<CellValueBase>(cvar);
} // initCelli

//returns the cellvaluebase reference pointer
CellValueBase* Cell::giveref()
{
	if (value != 0)
		return value.get();

	return NULL;
} // giveref


//*****************************************************
//Column
//vector<Cell*> class

//constructor
Column::Column(int size)
{
	this->size = size;
	for(int i = 0; i < size; i++)
		col.push_back(new Cell());
} // constructor

Column::~Column()
{
	while(!col.empty())
		col.pop_back();
} // destructor

//nested resize function in column
//saves complexity if written here
void Column::resize(int newsize)
{
	if(newsize > size)
		for(int i = size; i < newsize; i++)
			col.push_back(new Cell());

	else
		for(int i = size; i > newsize; i--)
			col.pop_back();
} // resize


//replace existing cell with new value int
template <typename T>
void Column::replaceCell(int index, T newvalue, string mem)
{
	col[index]->initCelli(newvalue, mem);
} // replaceCell


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

	return NULL;
}

//get last cell in the vector
Cell* Column::end()
{
	if(col.size() > 0)
		return col[col.size() - 1];

	return NULL;
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
		matrix.push_back(Column(h));
}

//destructor
Sheet::~Sheet()
{
	while(!matrix.empty())
		matrix.pop_back();
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
				matrix[i].resize(newh);

			for(int i = b; i < newb; i++)
				matrix.push_back(Column(newh));
		}
		else
		{
			//otherwise only remove vector elements and handle the rest with
			//mested function in column
			for(int i = b; i > newb; i--)
				matrix.pop_back();

			for(int i = 0; i < newb; i++)
				matrix[i].resize(newh);
		}
		this->h = newh;
		this->b = newb;
	}
}

//replaces cell with new value string
void Sheet::replaceCell(int x, int y, string value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
		matrix[x].replaceCell(y, value, mem);

	else
		cout << "Cell was not in scope of matrix" << endl;
}

//replaces cell with new value int
void Sheet::replaceCell(int x, int y, int value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
		matrix[x].replaceCell(y, value, mem);

	else
		cout << "Cell was not in scope of matrix" << endl;
}

//replaces cell with new value float
void Sheet::replaceCell(int x, int y, float value, string mem)
{
	if(x < b && y < h && x > -1 && y > -1)
		matrix[x].replaceCell(y, value, mem);

	else
		cout << "Cell was not in scope of matrix" << endl;
}

//get a cell in the matrix at coords (x, y)
Cell* Sheet::getCell(int x, int y)
{
	if(x < b && y < h && x > -1 && y > -1)
		return matrix[x].getCell(y);

	return NULL;
}

//get a cell in the matrix at coords (a - 'A', y - 1)
Cell* Sheet::getCell(char a, int y)
{
	if (a >= 'A' && a <= 'Z' && y < h + 1 && y > -1)
		return matrix[a - 'A'].getCell(y - 1);

	return NULL;
}
