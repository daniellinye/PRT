// spreadsheetEx1.cpp : Defines the entry point for the console application.

#include "SheetView.h"

#include <iostream>

using namespace std;

int main()
{
	Range r = Range();
	Sheet* matrix = new Sheet(12, 12);
	matrix->replaceCell(2, 2, 5);
	cout <<"main:"<< matrix->getCell(1, 1)->giveref()->convertfloat();
	r.initm(matrix);
	r.getCell(2,2)->initCelli(5);
	r.print();
	return 0;
}


