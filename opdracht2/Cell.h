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
	std::stringstream print();

    //returns typename T as type
	std::string givetid();

    //returns the value as float
    //is -1 when it's null
	float convertfloat();
};

template<typename T>
class CellValue : public CellValueBase
{
private:
    //initial value
	T tvalue;

    //specific float converters for types
	float convtni();

	float convtnf();

	float convtns();
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
	float convertfloat();

};

class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
public:
	void initCell();

	template<typename T>
	void initCell(T init);

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