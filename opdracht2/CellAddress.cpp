#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "CellAddress.h"

using namespace std;

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

void CellAddress::init(string input)
{
	int charsize = sizeof(input);
	if(charsize > 0)
	{
		try{
			if (input[0] - 'A' >= 0)
				this->x = atoi(&input[0]);
			for (int i = 1; i < charsize; i++)
				if (input[i] - '0' >= 0 && input[i] - '0' <= 9)
					this->y = this->y * 10 + atoi(&input[i]) - '0';
		} catch(exception e)
		{
			this->x = 0; this->y = 0;
		}

	}

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