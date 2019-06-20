
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include "Cell.h"


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
std::stringstream CellValue<std::string>::print(void)
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
std::string CellValue<std::string>::givetid()
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
float CellValue<std::string>::convertfloat()
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
	value = std::unique_ptr<CellValueBase>(new CellValue<std::string>(""));
}


//filters cells to proper value and initializes them
void Cell::initCell(std::string value)
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
			std::cout << "rip" << std::endl;
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
			std::cout << "rip" << std::endl;
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
	value = std::unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a string
void Cell::initCelli(std::string init)
{
	auto cvar = new CellValue<std::string>(init);
	delete &value;
	value = std::unique_ptr<CellValueBase>(cvar);
}

//inits the cell with a float
void Cell::initCelli(float init)
{
	auto cvar = new CellValue<float>(init);
	delete &value;
	value = std::unique_ptr<CellValueBase>(cvar);
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

CellFormula::CellFormula(float value, std::string origin)
{
	this->value.reset(nullptr);
	this->value = std::unique_ptr<CellValueBase>(new CellValue<std::string>(""));
	auto cvar = new CellValue<float>(value);
	this->value = std::unique_ptr<CellValueBase>(cvar);
	this->origin = origin;
}

