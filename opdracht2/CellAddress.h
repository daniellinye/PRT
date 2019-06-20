#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>

#ifndef CAHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define CAHVar  // wordt ge-include

//This class is relevant for formulas
//it keeps track of the two coordinates that are inbetween the values
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