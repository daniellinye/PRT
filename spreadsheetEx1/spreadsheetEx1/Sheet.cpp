#include "stdafx.h"
#include "Cell.cpp"
#include <vector>
#include <memory>
#include <sstream>


class Sheet
{
private:
	std::vector<std::vector<Cell>> cells;
	int h, b;
public:
	Sheet(int h, int b)
	{
		this->h = h;
		this->b = b;
	}


};