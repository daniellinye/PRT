
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
	return -1;
}


template <typename T>
float CellValue<T>::convtni()
{
	float temp = (float)tvalue;
	return temp;
}

template <typename T>
float CellValue<T>::convtnf()
{
	return tvalue;
}

template <typename T>
float CellValue<T>::convtns()
{
	int temp = 0;
	for (char chars : tvalue)
	{
		if (chars >= '0' && chars <= '9')
			temp = temp * 10 + (chars - '0');
	}
	return temp;
}

template <typename T>
CellValue<T>::CellValue(T init)
{
	this->tvalue = init;
}

template <typename T>
T CellValue<T>::formvalue()
{
	return tvalue;
}

template <typename T>
std::stringstream CellValue<T>::print(void) 
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}

template <typename T>
std::string CellValue<T>::givetid()
{
	return typeid(T).name();
}

//returns the value into a float
template <typename T>
float CellValue<T>::convertfloat()
{
	switch (typeid(T).name())
	{
	case typeid(float).name() :
		return convtnf;
		break;
	case typeid(int).name() :
		return convtni;
		break;
	case typeid(std::string).name() :
		return convtns;
		break;
	default:
		std::cout << "Case " << typeid(T).name() << " not implemented" << std::endl;
	}
}



Cell::Cell()
{
	value = unique_ptr<CellValueBase>();
}

template<typename T>
void Cell::initCell(T init)
{
	value.reset();
	value = unique_ptr<CellValue<T>>(init);
}

CellValueBase* Cell::giveref()
{
	if (value != 0)
	{
		return value.get();
	}
	return NULL;
}
	


