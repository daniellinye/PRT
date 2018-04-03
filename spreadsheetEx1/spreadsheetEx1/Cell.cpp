#include "stdafx.h"
#include <memory>
#include <sstream>

class CellValueBase
{
private:
	int iv; std::string sv; float fv;
public:
	virtual void destroy();
	virtual std::stringstream print();
	virtual float convtn();

};

template<typename T>
class CellValue final : public CellValueBase
{
private:
	T tvalue;
public:
	virtual void destroy();
	virtual std::stringstream print();
	virtual float convtn();
	CellValue(T init)
	{
		this->tvalue = init;
	}

	T formvalue()
	{
		return tvalue;
	}
};

void CellValue<int>::destroy()
{
	delete this;
}

void CellValue<float>::destroy()
{
	delete this;
}

void CellValue<std::string>::destroy()
{
	delete this;
}

std::stringstream CellValue<int>::print()
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}

std::stringstream CellValue<float>::print()
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}

std::stringstream CellValue<std::string>::print()
{
	std::stringstream ss;
	ss << tvalue;
	return ss;
}

float CellValue<int>::convtn()
{
	float temp = (float)tvalue;
	return temp;
}

float CellValue<float>::convtn()
{
	return tvalue;
}

float CellValue<std::string>::convtn()
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

	void initCell(CellValue<float>* val)
	{

	}

	void initCell(CellValue<std::string>* val)
	{

	}
	
};
