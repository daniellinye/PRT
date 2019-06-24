#include <iostream>

#include "SheetController.h"


int main ()
{
	SheetController *controller = new SheetController();
  controller->MainLoop();
	delete controller;
	return 0;
}
