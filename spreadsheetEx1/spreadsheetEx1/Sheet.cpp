#include "stdafx.h"
#include "Cell.cpp"
#include "Sheet.o"


class sheet
{
private:
	cell **spreadsheet;
	int h, b;
public:
	void initsheet(int h, int b)
	{
		cell **spsheet = new cell*[h];
		for (int i = 0; i < h; i++)
		{
			spsheet[i] = new cell[b];
		}
		this->spreadsheet = spsheet;
		this->h = h; 
		this->b = b;
	}

	void resizesheet(int h, int b)
	{
		cell **spsheet = this->spreadsheet;
		int temph = this->h, tempb = this->b;
		initsheet(h, b);
		for (int i = 0; i < h && i < temph; i++)
		{
			for (int j = 0; j < b && j < tempb; j++)
			{
				this->spreadsheet[i][j] = spsheet[i][j];
			}
		}
	}
};