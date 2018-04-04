#include "stdafx.h"
#include <memory>
#include <sstream>


class CellValueBase
{

};

template<typename T>
class CellValue final : public CellValueBase
{
private:
	T tvalue;
public:
	virtual void destroy(void) {};
	virtual std::stringstream print(void) {};
	virtual float convtn(void) {};
	CellValue(T init)
	{
		this->tvalue = init;
	}

	T formvalue()
	{
		return tvalue;
	}
};


void CellValue<int>::destroy(void)
{
	delete this;
}


void CellValue<float>::destroy(void)
{
	delete this;
}


void CellValue<std::string>::destroy(void)
{
	delete this;
}


std::stringstream CellValue<int>::print(void)
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}


std::stringstream CellValue<float>::print(void)
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}


std::stringstream CellValue<std::string>::print(void)
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}


float CellValue<int>::convtn(void)
{
	float temp = (float)tvalue;
	return temp;
}


float CellValue<float>::convtn(void)
{
	return tvalue;
}


float CellValue<std::string>::convtn(void)
{
	int temp = 0;
	for (char chars : tvalue)
	{
		if(chars >= '0' && chars <= '9')
			temp = temp * 10 + (chars - '0');
	}
	return temp;
}

class Cell
{
private:
	std::unique_ptr<CellValueBase> *value = nullptr;
public:
	template<typename T>
	void initCell()
	{
		value = new CellValue<T>;
	}

	template<typename T>
	CellValue<T>* giveref()
	{
		if (value != nullptr)
		{
			return giveref();
		}
		return NULL;
	}
	

};
