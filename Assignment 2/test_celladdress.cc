#include <iostream>
#include <vector>

#include "CellValue.h"


/* Controleert werking verschillende datatypes in CellValue */


int main ()
{
  std::vector<CellValueBase*> cells;

  cells.push_back(new CellValueBase());
  cells.push_back(new CellValue<int>(12));
  cells.push_back(new CellValue<float>(12.12321));
  cells.push_back(new CellValue<std::string>("dqsad"));

  while (!cells.empty())
  {
    std::cout << "literal: " << cells.back()->ReturnLiteral() << std::endl;
    std::cout << "string: " << cells.back()->ReturnString() << std::endl;
    std::cout << "float: " << cells.back()->ReturnFloat() << std::endl;
    delete cells.back();
    cells.pop_back();
  }

	return 0;
}
