#include <memory>
#include <sstream>
#include <iostream>
#include <vector>

class CellValueBase
{
	CellValueBase() {};
public:
	virtual std::stringstream print()
	{
		std::stringstream ss;
		return ss;
	}

	virtual std::string givetid()
	{
		return "nonetype";
	}

	virtual float convertfloat()
	{
		return 0;
	}
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
	CellValue(T init);

	T formvalue();

	std::stringstream print(void);

	std::string givetid();

	//returns the value into a float
	float convertfloat();

};
