#include <memory>
#include <sstream>
#include <iostream>
#include <vector>

struct CellValueBase
{
	CellValueBase() {};
public:
    //gives a stringstream with the 
    //value in the stringstream
    //is empty if it's null
	virtual std::stringstream print()
	{
		std::stringstream ss;
		return ss;
	}

    //returns typename T as type
	virtual std::string givetid()
	{
		return "nonetype";
	}

    //returns the value as float
    //is -1 when it's null
	virtual float convertfloat()
	{
		return -1;
	}
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
