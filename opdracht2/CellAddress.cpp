
#include <string>
#include <iostream>
#include "CellAddress.h"


CellAddress::CellAddress() {};

void CellAddress::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CellAddress::init(std::string input)
{
	if (input[0] - 'A' >= 0)
		this->x = input[0] - 'A';
	for (int i = 1; i < input.size() - 1; i++)
		if (input[i] - '0' >= 0 && input[i] - '0' <= 9)
			this->y = this->y * 10 + input[i] - '0';
}

int* CellAddress::givecoords()
{
	return new int[2]{ x, y };
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