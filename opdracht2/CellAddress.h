#include <string>
#include <iostream>


class CellAddress
{
private:
	int x, y;
public:
	CellAddress();

	void init(int x, int y);


	void init(std::string input);

	int* givecoords();

	CellAddress* operator +=(CellAddress &a);

	CellAddress* operator +=(int coords[2]);

};