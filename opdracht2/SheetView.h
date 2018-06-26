#include <iostream>
#include "Range.h"
#include <ncurses.h>
#include <math.h>   //for rounding the floats

using namespace std;

static const int cellheigth(1); //height of a single cell
static const int cellwidth(8);  //width of a single cell
static const int editwidth(16); //width of two cells, for editing window

class SheetView
{
public:
  Sheet* matrix;          //create a pointer to a Sheet
  CellAddress* address;   //create a pointer to a CellAddress
  int lines, cols;        //height and with of view
  Range r; //create a range
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
  void CreateBorder (WINDOW* win, int height, int width);

  //empty and refill the view with updated data
  void RefreshSheet(WINDOW* win, int x, int y);

  //create an edit subwindow and change a cell's value
  void StartEdit(WINDOW* win, int x, int y);

  //create the main window and display the view
	void Display();

};
