// spreadsheetEx1.cpp : Defines the entry point for the console application.
//

#include "Range.h"
#include <iostream>

using namespace std;

//TODO: fix segmentation fault
int main()
{
	Range r = Range();
	Sheet* matrix = new Sheet(12, 12);
	matrix->getCell(5 ,5);
	r.initm(matrix);
	r.print();
	return 0;
}


