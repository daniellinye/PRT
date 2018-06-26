// spreadsheetEx1.cpp : Defines the entry point for the console application.

#include "SheetView.h"
#include <iostream>
#include <assert.h>

using namespace std;


class MainTests
{
private:
	Range r;
	Sheet *matrix;
public:
	//constructor
	MainTests()
	{
		r = Range();
		matrix = new Sheet(12, 12);
		r.initm(matrix);
	}
	//*******************************************
	//tests

	void dotests()
	{
		assert(test1());
		assert(test2());
	}

	bool test1()
	{
		//tests memory values and overwrites
		try
		{
			r.initCell(4, 4, "42365");
			r.initCell(2, 2, "51.2121");
			r.initCell(2, 2, "522.2");
			float temp = r.getCell(4, 4)->giveref()->convertfloat();
			float temp2 = r.getCell(2, 2)->giveref()->convertfloat();
			string temp3 = r.getCell(2, 6)->giveref()->givetid();
			cout << "temp:" << temp << "|temp2:" << temp2 << "|temp3:" << temp3 << endl;
			return true;
		}
		catch(exception)
		{
			return false;
		}
	}

	bool test2()
	{
		//tests weird and odd writes
		try
		{
			r.initCell(-2, -2, "42365");
			r.initCell(-2, 0, "arwgiujfd");
			r.initCell(0, -8, "sadf@335");
			r.getCell(-2, -2);
			r.getCell(-2, 0);
			r.getCell(0, -8);
		}
		catch(exception)
		{
			return false;
		}
		return true;
	}

	bool test3()
	{
		try
		{
			r.initCell(0, 0, "0");
			r.initCell(0, 1, "1");
			r.initCell(0, 2, "2");
			r.initCell(1, 0, "3");
			r.initCell(2, 0, "4");
			r.initCell(1, 1, "5");
			r.initCell(2, 1, "6");
			r.initCell(1, 2, "7");
			r.initCell(2, 2, "8");
			string temp = r.iterRows("A0:C3", matrix);
			int temp2 = atoi(temp.c_str());
			if(temp2 == 36)
			{
				cout << "Tests complete" << endl;
			}
		}
		catch(exception)
		{
			return false;
		}
		return true;
	}
};

int main()
{
	//execute actual program
	SheetView view = SheetView();
	view.Display();
	return 0;
}
