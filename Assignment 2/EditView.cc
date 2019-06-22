#ifndef __EDV_CC__
#define __EDV_CC__

static const int cellheight(1); //height of a single cell
static const int cellwidth(8);  //width of a single cell

#include <iostream>
#include "EditView.h"

//*****************************************************************************

EditView::EditView(int x, int y)
{
  window = subwin(stdscr,cellheight,cellwidth,cellheight*(y+1),cellwidth*(x+1));
  keypad(window, TRUE);     // enable keyboard inputs
  curs_set(1);
} // constructor


EditView::~EditView()
{
  delwin(window);
  curs_set(0);
} // destructor


//Refreshes the editwindow
void EditView::Refresh(char *input, int curs_pos)
{
  int pos = 0;

  if (curs_pos >= cellwidth)
    pos = curs_pos - cellwidth + 1;

  werase(window);
  mvwprintw(window,0,0,input + pos);
  wmove(window,0,curs_pos);
  wrefresh(window);
} // Refresh


// Fetch a single character from ncurses
int EditView::GetChar()
{
  noecho();
  return getch();
} // GetChar


#endif
