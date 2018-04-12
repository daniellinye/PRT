// spreadsheetEx1.cpp : Defines the entry point for the console application.
//

#include "Range.cpp"
#include "SheetView.cpp"

int main()
{
	Range r = Range();
	SheetView view = SheetView();
	Sheet sheet = Sheet(view.retH(),view.retB());

	view.Display(r.returnSheet());

  return 0;
}
