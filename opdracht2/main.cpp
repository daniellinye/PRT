// spreadsheetEx1.cpp : Defines the entry point for the console application.
//

#include "Range.cpp"
#include <iostream>

//TODO: fix segmentation fault
int main()
{
	Range r = Range();
	Sheet* matrix = new Sheet(12, 12);
	r.initm(matrix);
	r.print();
	return 0;
}


