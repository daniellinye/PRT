#include <string>
#include <iostream>
#ifndef CellAddressHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define CellAddressHVar  // wordt ge-include 

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

#endif