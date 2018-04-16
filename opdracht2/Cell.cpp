
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#include "Cell.h"

using namespace std;

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



class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
public:
	void initCell()
	{
		value = unique_ptr<CellValueBase>();
	}

	CellValueBase* giveref()
	{
		if (value != 0)
		{
			return value.get();
		}
		return NULL;
	}
	
	
/*
	Cell* operator +=(Cell *& other)
	{
		if (value != nullptr && other->value != nullptr && giveref()->givetid() == other->giveref()->givetid())
		{
			float temp = value->convertfloat();
			temp += other->value->convertfloat();
			value = new CellValue<float>(temp);
		}
		return this;
	}

*/
};


