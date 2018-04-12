
#include "CellAddress.cpp"
#include "Sheet.cpp"

class Range
{
private:
	Sheet* matrix;
	CellAdress begin;
	CellAdress end;
public:
	Range() {};

	void initm(Sheet* matrix)
	{
		this->matrix = matrix;
	}

	void setbegin(int x, int y)
	{
		begin = CellAdress();
		begin.init(x, y);
	}

	void setend(int x, int y)
	{
		end = CellAdress();
		end.init(x, y);
	}
};

class RangeIterator : Range, CellAdress
{
private:
	Range begin;
	Range end;
public:
	RangeIterator() {};


};
