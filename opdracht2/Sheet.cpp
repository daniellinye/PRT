#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Sheet.h"
#include "Range.h"


//*****************************************************
//Column
//vector<Cell*> class

//constructor
Column::Column(int size)
{
	this->size = size;
	for(int i = 0; i < size; i++)
	{
		col.push_back(new Cell());
	}
}

//nested resize function in column
//saves complexity if written here
void Column::resize(int newsize)
{
	if(newsize > size)
	{
		for(int i = size; i < newsize; i++)
		{
			col.push_back(new Cell());
		}
	}
	else
	{
		for(int i = size; i > newsize; i--)
		{
			col.pop_back();
		}
	}
}

void Column::replaceCell(int index, int newvalue)
{
	col[index]->initCelli(newvalue);
}

void Column::replaceCell(int index, float newvalue)
{
	col[index]->initCelli(newvalue);
}

//replace existing cell with new value string
void Column::replaceCell(int index, std::string newvalue)
{
	col[index]->initCell(newvalue);
}

void Column::replaceCell(int index, float newvalue, std::string origin)
{
	delete col[index];
	col[index] = new CellFormula(newvalue, origin);
}

//get cellpointer from index
Cell* Column::getCell(int index)
{
	return col[index];
}

//get first cell in the vector
Cell* Column::begin()
{
	if(col.size() > 0)
		return col[0];
	else
		return new Cell();
}

//get last cell in the vector
Cell* Column::end()
{
	if(col.size() > 0)
		return col[col.size() - 1];
	else
		return new Cell();
}


//*****************************************************
//Sheet
//Vector<Column> class

//constructor
Sheet::Sheet(int h, int b)
{
	this->h = h;
	this->b = b;
	//fill matrix with h x b cells that are empty
	for(int i = 0; i < b; i++)
	{
		matrix.push_back(Column(h));
	}
}


//initializes a new cell, but filters the string
//such that formulas, int, float and string
//get the correct cell types
void Sheet::initCell(int x, int y, std::string value)
{
    Range r = Range();
	//first see if it's a formula
	try
	{
		std::string startparser = "", arg = "";
		float result = 0;
		int state = 0;
		if (value[0] == '=')
		{
			for(char val : value)
			{
				if(val == '(' && state == 0)
				{
					state = 1;
				}
				else if (state == 0)
				{
					startparser += val;
				}
				else if (state == 1 && val == ')')
				{
					state = 2;
				}
				else if (state == 1)
				{
					arg += val;
				}
			}//for

			if(startparser == "SUM")
			{
				result = r.iterRows(this, arg);
			} 
			else if(startparser == "COUNT")
			{
				result = r.countcells(this, arg);
			}
			else if (startparser == "AVG")
			{
				result = r.averageCells(this, arg);
			}
			else
			{
				//otherwise it's a string
				throw 0;
			}
			replaceCell(x, y, result, value);
				
		}//if val[0] = '='
		else
		{
			replaceCell(x, y, result);
		}
	}
	catch (int e)
	{
		std::cout << e << std::endl;
		replaceCell(x, y, value);
	}
}


//resizes the matrix
void Sheet::resize(int newh, int newb)
{
	//check wether the sizes are valid
	if(newh > 0 && newb > 0)
	{
		//in case the matrix has to become larger, make new vector elements
		if(newb > b)
		{
			for(int i = 0; i < b; i++)
			{
				matrix[i].resize(newh);
			}
			for(int i = b; i < newb; i++)
			{
				matrix.push_back(Column(newh));
			}
		}
		else
		{
			//otherwise only remove vector elements and handle the rest with
			//mested function in column
			for(int i = b; i > newb; i--)
			{
				matrix.pop_back();
			}
			for(int i = 0; i < newb; i++)
			{
				matrix[i].resize(newh);
			}
		}
		this->h = newh;
		this->b = newb;
	}
}

//replaces cell with new value string
void Sheet::replaceCell(int x, int y, std::string value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		std::cout << "Cell was not in scope of matrix" << std::endl;
	}
}

//replaces cell with new value int
void Sheet::replaceCell(int x, int y, int value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		std::cout << "Cell was not in scope of matrix" << std::endl;
	}
}

//replaces cell with new value float
void Sheet::replaceCell(int x, int y, float value)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value);
	}
	else
	{
		std::cout << "Cell was not in scope of matrix" << std::endl;
	}
}

void Sheet::replaceCell(int x, int y, float value, std::string origin)
{
	if(x < b && y < h && x > -1 && y > -1)
	{
		matrix[x].replaceCell(y, value, origin);
	}
	else
	{
		std::cout << "Cell was not in scope of matrix" << std::endl;
	}
}

//get a cell in the matrix at coords (x, y)
Cell* Sheet::getCell(int x, int y)
{
	if(x < b && y < h && x > -1 && y > -1)
		return matrix[x].getCell(y);
	else
		return new Cell();
}

//get a cell in the matrix at coords (a - 'A', y - 1)
Cell* Sheet::getCell(char a, int y)
{
	if (a >= 'A' && a <= 'Z' && y < h + 1 && y > -1)
		return matrix[a - 'A'].getCell(y - 1);
	else
		return new Cell();
}