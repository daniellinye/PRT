// spreadsheetEx1.cpp : Defines the entry point for the console application.

/*
observers
->deleteobserver.... so you don't get rekt

rangeiterator
->watch the endrange (don't miss the finish)
*/
//

#include "SheetView.h"
#include <iostream>

using namespace std;

//TODO: fix undefined reference to void Cell::initCell<int>(int)
int main()
{
	SheetView view = SheetView();
	view.Display();
	return 0;
}
