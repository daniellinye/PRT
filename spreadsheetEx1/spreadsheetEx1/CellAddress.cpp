#include "stdafx.h"
#include <string>
#include <iostream>


class CellAdress
{
private:
	int x, y;
public:
	CellAdress() {};
	void init(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void init(char input[])
	{
		if (input[0] - 'A' >= 0)
			this->x = input[0] - 'A';
		for (int i = 1; i < sizeof(input) - 1; i++)
			if (input[i] - '0' >= 0 && input[i] - '0' <= 9)
				this->y = this->y * 10 + input[i] - '0';
			else
				std::cout << "Value was not defined!" << "\n";
	}

	//actually createfromreference, but for convenience sake
	void init(std::string input)
	{
		if (input[0] - 'A' >= 0)
			this->x = input[0] - 'A';
		for (int i = 1; i < sizeof(input) - 1; i++)
			if (input[i] - '0' >= 0 && input[i] - '0' <= 9)
				this->y = this->y * 10 + input[i] - '0';
	}

	int* givecoords()
	{
		return new int[2]{ x, y };
	}

	CellAdress* operator +=(CellAdress &a)
	{
		int* coords = a.givecoords();
		this->x += coords[0];
		this->y += coords[1];
		return this;
	}

	CellAdress* operator +=(int coords[2])
	{
		this->x += coords[0];
		this->y += coords[1];
		return this;
	}

};