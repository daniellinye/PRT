#include <vector>
#include <memory>
#include <sstream>
#include <stdlib.h>

#ifndef SheetHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define SheetHVar  // wordt ge-include

using namespace std;

//This is the base class with basefunctions
//for the stored values in the program.
struct CellValueBase
{
	CellValueBase() {};
public:
    //gives a stringstream with the
    //value in the stringstream
    //is empty if it's null
	virtual std::stringstream print();

    //returns typename T as type
	virtual std::string givetid();

    //returns the value as float
    //is -1 when it's null
	virtual float convertfloat();
};

//This class extends to types from the basefunctions
//for the typings int, string and float with templates.
template<typename T>
class CellValue : public CellValueBase
{
private:
    //initial value
	T value;
	string memory;
public:
    //constructor
	CellValue(T init);

	//for cellformulas
	CellValue(T init, string memory);

    //returns the value in
    //type T
	T formvalue();

	//for formulas return memory cell
	string returnmemory();

	void update(T uvalue, string memory);

    //gives stringstream with value
	std::stringstream print(void);

    //gives typename T in string
	std::string givetid();

	//returns the value into a float
	virtual float convertfloat();

};

//This class is for formulas, it stores both a
//string and float in order to edit the string,
//but keep the float value intact.
class CellFormula : public CellValue<float>
{
private:
	float value;
	string originval;
public:
	//constructor
	CellFormula(string originval);

	//returns value
	float formvalue();

	//prints value into stringstream
	//important that this is value
	std::stringstream print();

	//gives typeid
	std::string givetid();

	//gives originval
	string giveorigin();

	//converts the value into a float
	virtual float convertfloat();
};

//Cell is the pointerclass to any CellValueBase and it's extensions.
//This is such that we can give different celltypes.
class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
public:
	//constructor
	Cell();

	//destructor
	~Cell();

	//initializes a new cell with an integer value init
	void initCelli(int init, string mem);

	//initializes a new cell with string value init
	void initCelli(string init, string mem);

	void initCelli(float init, string mem);

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};

//Matrix has columns,
//this is such that we can edit on a lower level.
//Column has a row of cells, which can be resized or replaced.
class Column
{
private:
	std::vector<Cell*> col;
	int size;
public:
	Column(int size);
	~Column();

	//resize vectorcolumns to proper size
	void resize(int newsize);

	//replaces a cell with value T
	template<typename T>
	void replaceCell(int index, T value, string mem);


	//gets cell from vector at col index
	Cell* getCell(int index);

	//returns the begin of the col cell
	Cell* begin();

	//returns the end of the col cell
	Cell* end();

};


//Sheet is a class with Columns
//it essentially is a matrix class with functions
//it can replace, get cells or resize
class Sheet
{
private:
	std::vector<Column> matrix;
	//temporary empty cell
	int h, b;
public:
	//initializes the sheet with
	//height h and width b
	Sheet(int h, int b);

	~Sheet();

	//resize matrix to new size h and b
	void resize(int newh, int newb);

	//try to make the string into float first, then int
	//if that doesn't work, then check if the cell is a formula
	//otherwise just make a stringcell
	void parseCell(int x, int y, string value);

	//replaces cell at virtual coords x and y with value int
	void replaceCell(int x, int y, int value, string mem);

	//replaces a cell at virtual coords x and y with value string
	void replaceCell(int x, int y, string value, string mem);

	//replaces a cell at virtual coords x and y with value float
	void replaceCell(int x, int y, float value, string mem);

	//gets a cell at coords x and y
	Cell* getCell(int x, int y);

	//gets a cell at coords char a and int y
	//Note: relative coords A1 correspond to "(0, 0)"
	Cell* getCell(char a, int y);

	//returns the begin of a cell in a column
	Cell* begin(int column);

	//returns the end of a cell in a column
	Cell* end(int column);
};

#endif
