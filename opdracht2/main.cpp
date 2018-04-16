// spreadsheetEx1.cpp : Defines the entry point for the console application.
//

#include "Range.h"
#include <iostream>

using namespace std;

//TODO: fix undefined reference to void Cell::initCell<int>(int)
int main()
{
	Range r = Range();
	Sheet* matrix = new Sheet(12, 12);
	r.initm(matrix);
	r.getCell(2,2)->initCell(5);
	r.print();
	return 0;
}


