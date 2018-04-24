#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#ifndef CellHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define CellHVar  // wordt ge-include 


using namespace std;

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
	virtual std::stringstream print();

    //gives typename T in string
	std::string givetid();

	//returns the value into a float
	virtual float convertfloat();

};

class CellFormula : public CellValueBase
{
private:
	string parse;
	float value;
public:
	CellFormula();

	//initializes the class with sum value string
	void init(string init);

	//grabs the sums of a stringstream input
	void parsesum(stringstream values);

	//returns in a print the value;
	virtual stringstream print();

	//gives typename in string
	string givetid();

	//returns the value into a float
	virtual float convertfloat();
};

class Cell
{
private:
	unique_ptr<CellValueBase> value;
public:
	Cell();

	void initCell();

	void initCelli(int init);
	void initCelli(string init);

	CellValueBase* giveref();
	
	
/*
	Cell* operator +=(Cell *& other)
	{
		if (value != nullptr && other->value != nullptr && giveref()->givetid() == other->giveref()->givetid())
		{
			float temp = value->convertfloat();
			temp += other->value->convertfloat();
			value = new CellValue<float>(temp);
		}
		return this;
	}

*/
};

#endif