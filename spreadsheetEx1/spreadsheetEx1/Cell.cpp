#include "stdafx.h"
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>


class CellValueBase
{
	CellValueBase() {};
public:
	virtual void destroy() { delete this; }
	virtual std::stringstream print()
	{
		std::stringstream ss;
		return ss;
	}

	virtual std::string givetid()
	{
		return "nonetype";
	}

	virtual float convertfloat()
	{
		return 0;
	}
};

template<typename T>
class CellValue : public CellValueBase
{
private:
	T tvalue;

	float convtni()
	{
		float temp = (float)tvalue;
		return temp;
	}

	float convtnf()
	{
		return tvalue;
	}

	float convtns()
	{
		int temp = 0;
		for (char chars : tvalue)
		{
			if (chars >= '0' && chars <= '9')
				temp = temp * 10 + (chars - '0');
		}
		return temp;
	}

public:
	CellValue(T init)
	{
		this->tvalue = init;
	}

	T formvalue()
	{
		return tvalue;
	}

	virtual void destroy(void) { delete this };
	virtual std::stringstream print(void) 
	{
		ss << tvalue;
		return ss;
	};
	virtual float convtn(void) {};


	virtual std::string givetid()
	{
		return typeid(T).name();
	}

	//returns the value into a float
	virtual float convertfloat()
	{
		switch (typeid(T))
		{
		case typeid(float) :
			return convtnf;
			break;
		case typeid(int) :
			return convtni;
			break;
		case typeid(std::string) :
			return convtns;
			break;
		default:
			std::cout << "Case " << typeid(T).name() << " not implemented" << endl;
		}
	}
};





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
