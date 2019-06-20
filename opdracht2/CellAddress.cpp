#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include "CellAddress.h"


//*****************************************************
//CellAddrress

CellAddress::CellAddress()
{
	this->x = 0;
	this->y = 0;
};

//constructor
void CellAddress::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

//constructor
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

// returns coords in array
int* CellAddress::givecoords()
{
	return new int[2]{ x, y };
}

//returns x coord
int CellAddress::givex()
{
	return x;
}

//returns y coord
int CellAddress::givey()
{
	return y;
}

//operator += for another Celladdress object
CellAddress* CellAddress::operator +=(CellAddress &a)
{
	int* coords = a.givecoords();
	this->x += coords[0];
	this->y += coords[1];
	return this;
}

//operator += for another array object
CellAddress* CellAddress::operator +=(int coords[2])
{
	this->x += coords[0];
	this->y += coords[1];
	return this;
}



