
#include <string>
#include <iostream>
#include "CellAddress.h"


CellAddress::CellAddress()
{
	this->x = 0;
	this->y = 0;
};

void CellAddress::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CellAddress::init(std::string input)
{
	int i = 0;
	int size = input.size();
	if (size > 0)
	{
		this->x = 0;
		this->y = 0;
		while (!isdigit(input[i])){
			this->x = (this->x) * 26 + input[i] - 'A' + 1;
			i++;
		}
		for (; i < size; i++) {
			if (isdigit(input[i])){
				this->y = this->y * 10 + input[i] - '0';
			}
		}
	}
	this->x -= 1;
	this->y -= 1;
}

int* CellAddress::givecoords()
{
	return new int[2]{ x, y };
}

int CellAddress::givex()
{
	return x;
}

int CellAddress::givey()
{
	return y;
}

CellAddress* CellAddress::operator +=(CellAddress &a)
{
	int* coords = a.givecoords();
	this->x += coords[0];
	this->y += coords[1];
	return this;
}

CellAddress* CellAddress::operator +=(int coords[2])
{
	this->x += coords[0];
	this->y += coords[1];
	return this;
}
