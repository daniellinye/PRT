
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

void CellValueBase::parsesum(stringstream & ss)
{

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

template<>
void CellValue<string>::parsesum(stringstream & ss)
{

}

template<>
void CellValue<int>::parsesum(stringstream & ss)
{

}

template<>
void CellValue<float>::parsesum(stringstream & ss)
{

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

void Cell::initFormula(string init, stringstream & ss)
{
	auto cvar = new CellFormula(init, ss);
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


CellFormula::CellFormula(string init, stringstream & ss) 
{
	if(init[0] == '=')
		this->parse = init;
	parsesum(ss);
}



void CellFormula::parsesum(stringstream & ss)
{
	string parser;
	int temp, total = 0;
	try
	{
		while(ss.rdbuf()->in_avail() != 0)
		{
			ss >> parser;
			temp = atoi(parser.c_str());
			total += temp;
		}
		this->value = total;
	} catch(exception e)
	{
		this->parse = "ERR";
	}
}

stringstream CellFormula::print()
{
	stringstream ss;
	if(this->value != NULL)
	{
		ss << value;
	}
	return ss;
}

std::string CellFormula::givetid()
{
	return "nonetype";
}

float CellFormula::convertfloat()
{
	return this->value;
}

	


