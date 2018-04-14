#include <memory>
#include <sstream>
#include <iostream>
#include <vector>



class CellValueBase
{
public:
	CellValueBase();

    //gives a stringstream with the printed value back
	virtual std::stringstream print();

    //returns the type of the value inserted
	virtual std::string givetid();

    //converts the value to a float
	virtual float convertfloat();

};

template<typename T>
class CellValue : public CellValueBase
{
private:
	T tvalue;
    float convtni();
    float convtnf();
    float convtns();
public:
    //initializes the value in type T
	CellValue(T init);

    //returns the value in type T
	T formvalue();

    //gives the value into a stringstream
	virtual std::stringstream print(void);

    //returns the valuetype
	virtual std::string givetid();


	//returns the value into a float
	virtual float convertfloat();

};

