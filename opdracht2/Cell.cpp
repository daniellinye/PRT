
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#include "Cell.h"

using namespace std;



std::stringstream CellValueBase::print()
{
	std::stringstream ss;
	ss << " ";
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
	cout <<"d";
	return -1;
}

template <typename T>
CellValue<T>::CellValue(T init) : CellValueBase()
{
	this->value = init;
}

template <typename T>
T CellValue<T>::formvalue()
{
	return value;
}

template <>
std::stringstream CellValue<float>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

template <>
std::stringstream CellValue<int>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

template <>
std::stringstream CellValue<string>::print(void)
{
	std::stringstream ss;
	ss << value;
	return ss;
}

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

template<>
float CellValue<string>::convertfloat()
{
	float temp = 0;
	for (char chars : value)
	{
		if (chars >= '0' && chars <= '9')
			temp = temp * 10 + (chars - '0');
	}
	return temp;
}

template<>
float CellValue<float>::convertfloat()
{
	//TODO: has to be "value" from the extended class
	return value;
}

Cell::Cell()
{
	value.reset(nullptr);
	value = unique_ptr<CellValueBase>(new CellValue<string>(""));
}


void Cell::initCelli(int init)
{

	auto cvar = new CellValue<int>(init);
	value = unique_ptr<CellValueBase>(cvar);
}



void Cell::initCelli(string init)
{

	auto cvar = new CellValue<string>(init);
	value = unique_ptr<CellValueBase>(cvar);
}


CellValueBase* Cell::giveref()
{
	if (value != 0)
	{
		return value.get();
	}
	return NULL;
}
