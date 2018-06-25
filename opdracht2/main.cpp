// spreadsheetEx1.cpp : Defines the entry point for the console application.

#include "SheetView.h"
#include <iostream>
#include <assert.h>

using namespace std;


class MainTests
{
private:
	SheetView sv;
public:
	//constructor
	MainTests()
	{
		sv = SheetView();
	}
	//*******************************************
	//tests

	void dotests()
	{
		assert(test1());
	}

	bool test1()
	{
		return true;
	}
};

int main()
{
	//initialize and to unit assert tests
	MainTests mt = MainTests();
	mt.dotests();

	//execute actual program
	SheetView view = SheetView();
	view.Display();
	return 0;
}
