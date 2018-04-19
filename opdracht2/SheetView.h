#include <iostream>
#include "Range.h"
#include <ncurses.h>

class SheetView
{
private:
  Range r;
  Sheet* matrix;
public:
  SheetView();

  void RowCol(WINDOW *win);

  void FillSheet(WINDOW *win);

//  void CreateCursor ();

	void Display();

};
