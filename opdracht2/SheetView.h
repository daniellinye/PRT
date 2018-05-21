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
  //constructor
  SheetView();

  //check whether given x -and y-coordinates are in the view
  bool isinview(int x, int y);

  //add row -and columnnames to view
  void RowCol(WINDOW *win);

  //check whether a given string (that starts with '=') is a formula, and change
  // the string to the result of that formula
  void CheckFormula(std::string &str);

  //print a cell with the coordinates x and y
  void PrintCell(WINDOW* win, int x, int y);

  //call PrintCell from every cell in the view
  void FillSheet(WINDOW *win);

  //add a border around the editing subwindow
  void CreateBorder (WINDOW* win);

  //empty and refill the view with updated data
  void RefreshSheet(WINDOW* win, int x, int y);

  //create an edit subwindow and change a cell's value
  void StartEdit(WINDOW* win, int x, int y);

  //create the main window and display the view
	void Display();

};
