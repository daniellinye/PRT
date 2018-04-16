#include "Sheet.h"
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

Sheet::Sheet(int h, int b)
{
	this->h = h;
	this->b = b;
	//fill matrix with h x b cells that are empty
	for(int i = 0; i < b; i++)
	{
		matrix.push_back(Column(h));
		for(int j = 0; j < h; j++)
		{

		}
	}
}

CellValueBase* Sheet::getCell(int x, int y)
{
	return matrix[x].getCell(y)->giveref();
}

CellValueBase* Sheet::getCell(char a, int y)
{
	if (a >= 'A' && a <= 'Z')
		return matrix[a - 'A'].getCell(y)->giveref();
	else
		return NULL;
}

//TODO: move to class Range
Cell* Sheet::begin(int column)
{
	return matrix[column].begin();
}

//TODO: move to class Range
Cell* Sheet::end(int column)
{
	return matrix[column].end();
}

void Sheet::print()
{
	int tx = 0;
	for(int i = 0; i < b; i++)
	{
		for(int j = 0; j < h; j++)
		{
			cout << matrix[i].getCell(j)->giveref()->convertfloat();
		}
		cout << endl;
	}
}


Column::Column(int size)
{
	this->size = size;
	for(int i = 0; i < size; i++)
	{
		col.push_back(new Cell());
	}
}

Cell* Column::getCell(int index)
{
	return col[index];
}

Cell* Column::begin()
{
	if(col.size() > 0)
		return col[0];
	else
		return new Cell();
}

Cell* Column::end()
{
	if(col.size() > 0)
		return col[col.size() - 1];
	else
		return new Cell();
}