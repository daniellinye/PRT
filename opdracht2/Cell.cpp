
#include "Cell.h"
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>


CellValueBase::CellValueBase() {};

std::stringstream CellValueBase::print()
{
	std::stringstream ss;
	return ss;
}

std::string CellValueBase::givetid()
{
	return "nonetype";
}

float CellValueBase::convertfloat()
{
	return 0;
}


template<typename T>
float CellValue<T>::convtni()
{
	float temp = (float)tvalue;
	return temp;
}

template<typename T>
float CellValue<T>::convtnf()
{
	return tvalue;
}

template<typename T>
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

template<typename T>
CellValue<T>::CellValue(T init)
{
	this->tvalue = init;
}

template<typename T>
T CellValue<T>::formvalue()
{
	return tvalue;
}

template<typename T>
std::stringstream CellValue<T>::print(void)
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
};

template<typename T>
std::string CellValue<T>::givetid()
{
	return typeid(T).name();
}

//returns the value into a float
template<typename T>
float CellValue<T>::convertfloat()
{
	switch (typeid(T))
	{
	case typeid(float) :
		return convtnf();
		break;
	case typeid(int) :
		return convtni();
		break;
	case typeid(std::string) :
		return convtns();
		break;
	default:
		std::cout << "Case " << typeid(T).name() << " not implemented" << std::endl;
	}
}






class Cell
{
private:
	CellValueBase *value = nullptr;
public:
	template<typename T>
	void initCell(T initv)
	{
		value = new CellValue<T>(initv);
	}

	CellValueBase* giveref()
	{
		if (value != nullptr)
		{
			return value;
		}
		return NULL;
	}

	/*
	TODO: still need to fix this
	Cell* operator +=(Cell *& other)
	{
		if (value != nullptr && other->value != nullptr && giveref()->givetid() == other->giveref->givetid())
		{
			float temp = value->convertfloat();
			temp += other->value->convertfloat();
			value = new CellValue<float>(temp);
		}
		return this;
	}

	Cell* operator+=(std::vector<Cell*> cells)
	{
		if (value != nullptr)
		{
			for (Cell *cell : cells)
			{
				value += cell;
			}
		}
	}
	*/
};
