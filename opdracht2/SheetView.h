#include <iostream>
#include "Range.h"
#include <ncurses.h>
#include <math.h>   //for rounding the floats

static int lines(24);     //amount of lines in the sheet
static int cols(80);      //amount of columns in the sheet
static const int cellheigth(1); //height of a single cell
static const int cellwidth(8);  //width of a single cell
static const int maxwidth(16);  //width of a double cell
                                //(the maximum length of a cellvalue while editing)

class SheetView
{
private:
  Range r;                //create a range
  Sheet* matrix;          //create a pointer to a Sheet
  CellAddress* address;   //create a pointer to a CellAddress
public:
  SheetView();

  bool isinview(int x, int y);

  void RowCol(WINDOW *win);

  void CheckFormula(std::string &str);

  void PrintCell(WINDOW* win, int x, int y);

  void FillSheet(WINDOW *win);

  void CreateBorder (WINDOW* win);

  void RefreshSheet(WINDOW* win, int x, int y);

  void StartEdit(WINDOW* win, int x, int y);

	void Display();

};
