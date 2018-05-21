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
	std::stringstream print(void);

    //gives typename T in string
	std::string givetid();

	//returns the value into a float
	virtual float convertfloat();

};

class Cell
{
private:
	//initializes as 0's
	//that's why it first has the compile error
	unique_ptr<CellValueBase> value;
public:
	//constructor
	Cell();

	//initializes a new cell with an integer value init
	void initCelli(int init);

	//initializes a new cell with string value init
	void initCelli(string init);

	//gives the original reference of the unique_ptr
	CellValueBase* giveref();
};

#endif
