#ifndef __SHV_CC__
#define __SHV_CC__

static const int cellheight(1); //height of a single cell
static const int cellwidth(8);  //width of a single cell

#include <iostream>
#include "SheetView.h"

//*****************************************************
//Sheetview

//constructor
SheetView::SheetView()
{
  initscr();                //start of ncurses

  lines = 24;
  cols = 80;

  address = new CellAddress();
  sheet = new Sheet(lines, cols);

  CreateWindow();
  InitView();
  RefreshSheet();

  keypad(stdscr, TRUE);     // enable keyboard inputs
  curs_set(0);
} // SheetView


//destructor
SheetView::~SheetView()
{
  delete sheet;
  delete address;

  delwin(window); //delete window
  delwin(stdscr); //delete stdscr
  endwin();       //end of ncurses
} // ~SheetView


// Fetch a single character from ncurses
int SheetView::GetChar()
{
  noecho();
  return getch();
} // GetChar


// moves cursor to other cell
void SheetView::Move(int input)
{
  int x = address->x;
  int y = address->y;

  switch (input)
  {
    case KEY_UP:
      if (y > 0)
        y--;
    break;
    case KEY_RIGHT:
      if (x < maxcols - 1 && x < cols - 1)
        x++;
    break;
    case KEY_DOWN:
      if (y < maxlines - 1 && y < lines - 1)
        y++;
    break;
    case KEY_LEFT:
      if (x > 0)
        x--;
    break;
  } //switch

  address->SetAddress(x,y);
  RefreshSheet();
} // Move


// Delete value in selected cell
void SheetView::Delete()
{
  int x = address->x;
  int y = address->y;

  sheet->GetCell(x,y)->SetValue(nullptr);
  RefreshSheet();
} // Delete


// Creates an edit window
void SheetView::InitEdit()
{
  int x = address->x;
  int y = address->y;
  char *cellvalue;
  EditController *edit;

  CreateBorder();

  cellvalue = const_cast<char*>(sheet->GetCell(x,y)->GetLiteral().c_str());
  edit = new EditController(x,y,cellvalue);

  edit->EditLoop();
  sheet->GetCell(x,y)->SetValue(edit->CellValueFactory());
  RefreshSheet();

  delete edit;
} // InitEdit


// Create window
void SheetView::CreateWindow()
{
  int scrheight,scrwidth;
  getmaxyx(stdscr,scrheight,scrwidth);

  maxcols = (scrwidth / cellwidth) - 1;     // sets maximum amount
  maxlines = (scrheight / cellheight) - 1;  // of lines and columns

  window = subwin(stdscr, scrheight - cellheight, scrwidth - cellwidth, cellheight, cellwidth);
} // CreateWindow


// Add rows and colums
void SheetView::InitView()
{
  const int letters = 'Z' - 'A' + 1;
  char* colname = new char[cellwidth - 1];
  short aantalletters;
  float hulpflt;
  int letteri;

  attron(A_STANDOUT);             // Row -and collumn names are printed black on white

  //add column names
  for (int i = 0; i < cols && i < maxcols; i++)
  {
    aantalletters = 1;
    hulpflt = i;
    letteri = 0;
    while (hulpflt >= letters)
    {
      hulpflt = hulpflt / letters - 1;
      aantalletters++;
    } // while
    while (letteri < aantalletters)
    {
      colname[letteri] = 'A' + hulpflt;
      hulpflt = (hulpflt - (int) hulpflt) * letters;
      letteri++;
    } // while
    colname[letteri] = '\0';
    mvprintw(0,cellwidth * (i + 1),"   %*s",3 - cellwidth,colname);
  } // for

  //add rownumbers
  for (int i = 1; i <= lines && i <= maxlines; i++)
    mvprintw(cellheight * i, 0,"%*d   ",cellwidth - 3,i);

  attroff(A_STANDOUT);
  delete[] colname;
} // InitView


// Refreshes the window to the sheet
void SheetView::RefreshSheet()
{
  int x,y;
  const char* cellvalue;
  werase(window);

  for (x = 0; x < cols && x < maxcols; x++)
    for (y = 0; y < lines && y < maxlines; y++)
      PrintCell(x,y);

  x = address->x;
  y = address->y;

  cellvalue = sheet->GetCell(x,y)->GetValue().c_str();

  wattron(window,A_STANDOUT);
  mvwprintw(window,cellheight * y,cellwidth * x,"%*s",cellwidth,cellvalue);
  wattroff(window,A_STANDOUT);

  wrefresh(window);
} // RefreshSheet


// Prints cell
void SheetView::PrintCell(int x, int y)
{
  const char* cellvalue = sheet->GetCell(x,y)->GetValue().c_str();
  mvwprintw(window,cellheight * y,cellwidth * x,"%.*s",cellwidth,cellvalue);
} // PrintCell


// Print a border around the editwindow
void SheetView::CreateBorder()
{
  int x = address->x;
  int y = address->y;
  char corner = '+', vertical = '|', horizontal = '-';

  if(x > 0 && y > 0)
    mvwaddch(window, (cellheight * y) - 1, (cellwidth * x) - 1, corner);

  if(x < maxcols && x < cols && y > 0)
    mvwaddch(window, (cellheight * y) - 1, cellwidth * (x + 1), corner);

  if(x > 0 && y < maxlines && y < lines)
    mvwaddch(window, cellheight * (y + 1), (cellwidth * x) - 1, corner);

  if(x < maxcols && x < cols && y < maxlines && y < lines)
    mvwaddch(window, cellheight * (y + 1), cellwidth * (x + 1), corner);

  if(y > 0)
    mvwhline(window, (cellheight * y) - 1, cellwidth * x, horizontal, cellwidth);

  if(y < maxlines && y < lines)
    mvwhline(window, cellheight * (y + 1), cellwidth * x, horizontal, cellwidth);

  if(x > 0)
    mvwvline(window, cellheight * y, (cellwidth * x) - 1, vertical, cellheight);

  if(x < maxcols && x < cols)
    mvwvline(window, cellheight * y, cellwidth * (x + 1), vertical, cellheight);

  wrefresh(window);
} // CreateBorder

#endif
