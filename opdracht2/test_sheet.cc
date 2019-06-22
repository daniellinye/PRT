#include <iostream>

#include "Sheet.h"


int main ()
{

	Sheet *sheet = new Sheet(5,24);
	CellValueBase *cvb = new CellValue<int>(124);

	sheet->GetCell(4,2)->SetValue(cvb);

	std::cout << sheet->GetCell(1,2)->GetValue() << std::endl;
	std::cout << sheet->GetCell(4,2)->GetValue() << std::endl;

	delete sheet;
	return 0;
}
