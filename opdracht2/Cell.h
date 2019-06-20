
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <stdlib.h>

#ifndef CelHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define CelHVar  // wordt ge-include

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
public:
    //constructor
	CellValue(T init);

    //returns the value in
    //type T
	T formvalue();

    //gives stringstream with value
	std::stringstream print(void);

    //gives typename T in string
	std::string givetid();

	//returns the value into a float
	virtual float convertfloat();

};



//Cell is the pointerclass to any CellValueBase and it's extensions.
//This is such that we can give different celltypes.
class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	std::unique_ptr<CellValueBase> value;
public:
	//constructor
	Cell();

	void initCell(std::string value);

	//initializes a new cell with an integer value init
	void initCelli(int init);

	//initializes a new cell with string value init
	void initCelli(std::string init);

	void initCelli(float init);

	std::string givetype();

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};


//This class is for formulas, it stores both a 
//string and float in order to edit the string,
//but keep the float value intact.
class CellFormula : public Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	std::unique_ptr<CellValueBase> value;
	std::string origin;
public:
	//constructor
	CellFormula(float value, std::string origin);

	void initCell(float value, std::string origin);

	//initializes a new cell with an integer value init
	void initCelli(int init);

	//initializes a new cell with string value init
	void initCelli(std::string init);

	void initCelli(float init);

	std::string givetype();

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};

#endif