// spreadsheetEx1.cpp : Defines the entry point for the console application.

#include "SheetView.h"
#include <assert.h>
#include <iostream>

using namespace std;

//*************************************************
//main

int main()
{
	SheetController *controller = new SheetController();
  controller->MainLoop();
	delete controller;
	return 0;
}
