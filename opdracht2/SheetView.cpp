
#include "SheetView.h"
#include <ncurses.h>

static const int lines(24);
static const int cols(80);
static const int cellheigth(1);
static const int cellwidth(8);

SheetView::SheetView()
{
  r = Range();
  Sheet* matrix = new Sheet(lines, cols);
  matrix->replaceCell(2, 2, 5);
  cout <<"main:"<< matrix->getCell(2, 2)->giveref()->convertfloat();
  r.initm(matrix);
  r.getCell(2,2)->initCelli(5);
  r.print();
}

//add row and column names
void SheetView::RowCol(WINDOW *win)
{
  int i,n;
  char cell[cellwidth];

  wattron(win, A_STANDOUT);

  //add rownumbers
  for (i = 1; i < lines; i++) {
    wmove(win, cellheigth * i, 0);
    sprintf(cell,"   %d",i);
    for (n = 0; n < cellwidth; n++) {
      if (!cell[n]) {cell[n] = ' ';}
    }
    waddstr(win, cell);
  }

  //add column names
  for (i = 1; i < cols; i++) {
    wmove(win, 0, cellwidth * i);
    for (n = 0; n < cellwidth; n++) {
      cell[n] = ' ';
    }
    cell[3] = i + 'A' - 1;
    waddstr(win, cell);
  }
  wattroff(win, A_STANDOUT);
}//RowCol

//TODO: implement all cells from Sheet.cpp
void SheetView::FillSheet(WINDOW *win)
{
  int x,y;
  float value = 1;
  char cell[cellwidth];
  for (x = 0; x < cols; x++) {
    for (y = 0; y < lines; y++) {
      value = r.getCell(x,y)->giveref()->convertfloat();
      sprintf(cell,"%f",value);
      wmove(win, y + 1, x + 1);
      waddstr(win, cell);
    }
  }
}//FillSheet
/*
void SheetView::CreateCursor ()
{
  mvaddch(y, x, win->border.corner);
  mvaddch(y, x + w, win->border.top);
  mvaddch(y + h, x, win->border.corner);
  mvaddch(y + h, x + w, win->border.br);
  mvhline(y, x + 1, win->border.ts, w - 1);
  mvhline(y + h, x + 1, win->border.bs, w - 1);
  mvvline(y + 1, x, win->border.ls, h - 1);
  mvvline(y + 1, x + w, win->border.rs, h - 1);
}
*/
//Initialize window
void SheetView::Display()
{
  int ch;
  initscr(); //start of ncurses

  //create a new window
  WINDOW *win = newwin(cellheigth*lines, cellwidth*cols, 0, 0);
  keypad(win, TRUE); //enable keyboard inputs

  attr_t old_attr; //remember parameters
  short old_pair;
  wattr_get(win, &old_attr, &old_pair, NULL);

  RowCol(win);
  FillSheet(win);

  wattr_set(win, old_attr, old_pair, NULL); //reset previous parameters
  wrefresh(win); //display the created window
  while ((ch = wgetch(win)) != '\n'); //wait for an ENTER-input
  delwin(win); //delete window
  endwin(); //end of ncurses
}//Display
