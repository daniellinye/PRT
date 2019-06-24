#include <iostream>

#include "Range.h"


int main ()
{
  Sheet *sheet = new Sheet(24,80);
	Range *range = new Range(sheet, "=(F1:AD23)");

/*
  std::cout << "coordinate 1:"  << std::endl
            << "x: " << begin.x << std::endl
            << "y: " << begin.y << std::endl;

  std::cout << "coordinate 2:" << std::endl
            << "x: " << end.x  << std::endl
            << "y: " << end.y  << std::endl;
*/

	delete range;
  delete sheet;
	return 0;
}
