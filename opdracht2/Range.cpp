
#include "CellAddress.h"
#include "Sheet.h"

class Range
{
private:
	Sheet* matrix;
	CellAddress begin;
	CellAddress end;
public:
	Range() {};

	void initm(Sheet* matrix)
	{
		this->matrix = matrix;
	}

	void setbegin(int x, int y)
	{
		begin = CellAddress();
		begin.init(x, y);
	}

	void setend(int x, int y)
	{
		end = CellAddress();
		end.init(x, y);
	}

	void print()
	{
		matrix->print();
	}

	CellValueBase* getCell(int x, int y)
	{
		return matrix->getCell(x, y);
	}
};


