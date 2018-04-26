#include <string>
#include <iostream>
#ifndef CellAddressHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define CellAddressHVar  // wordt ge-include

class CellAddress
{
private:
	int x, y;
public:
	//constructor
	CellAddress();

	//initializes values x and y corresponding
	//with coordinates in the sheet
	void init(int x, int y);

	//initializes values x and y corresponding
	//with coordinates in the sheet
	//but takes input as string: <column><row>
	void init(std::string input);

	//returns the coordinates in a int[2]
	int* givecoords();

	//returns the x-coordinate
	int givex();

	//returns the y-coordinate
	int givey();

	//adds another celladress to the current one
	CellAddress* operator +=(CellAddress &a);

	//adds another coordinate(s) to the current one
	CellAddress* operator +=(int coords[2]);

};

#endif
