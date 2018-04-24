
#include "SheetView.h"
#include <ncurses.h>

SheetView::SheetView()
{
  r = Range();
  matrix = new Sheet(lines, cols);
  r.initm(matrix);
  address = new CellAddress();
}

bool SheetView::isinview(int x, int y)
{
  if (x >= cellwidth && x < (cols + 1) * cellwidth){
    if (y >= cellheigth && y < (lines + 1) * cellheigth){
      return true;
    }
  }
  return false;
}//check whether cell is in view

//add row and column names
void SheetView::RowCol(WINDOW *win)
{
  int i,n;
  char cell[cellwidth];

  wattron(win, A_STANDOUT);

  //add rownumbers
  for (i = 1; i <= lines; i++) {
    wmove(win, cellheigth * i, 0);
    sprintf(cell,"   %d",i);
    for (n = 0; n < cellwidth; n++) {
      if (!cell[n]) {cell[n] = ' ';}
    }
    waddstr(win, cell);
  }

  //add column names
  for (i = 1; i <= cols; i++) {
    wmove(win, 0, cellwidth * i);
    for (n = 0; n < cellwidth; n++) {
      cell[n] = ' ';
    }
    cell[3] = i + 'A' - 1;
    waddstr(win, cell);
  }
  wattroff(win, A_STANDOUT);
}//RowCol

//print cell
void SheetView::PrintCell(WINDOW* win, int x, int y, char cell[cellwidth])
{
  float value = r.getCell(x,y)->giveref()->convertfloat();
  sprintf(cell," %.2f",value);
  wmove(win, cellheigth*(y + 1), cellwidth*(x + 1));
  waddstr(win, cell);
}//PrintCell

//implement all cells from Sheet
void SheetView::FillSheet(WINDOW *win)
{
  int x,y;
  char cell[cellwidth];
  for (x = 0; x < cols; x++) {
    for (y = 0; y < lines; y++) {
      PrintCell(win,x,y,cell);
    }
  }
}//FillSheet

void SheetView::CreateCursor (WINDOW* win)
{
  int* coords = address->givecoords();
  int x = cellwidth*(coords[0] + 1);
  int y = cellheigth*(coords[1] + 1);
  char corner = '+', vertical = '|', horizontal = '-';

  if(isinview(x-1,y+1)){
    mvwaddch(win, y + 1, x - 1, corner);
  }
  if(isinview(x+1,y+1)){
    mvwaddch(win, y + 1, x + cellwidth, corner);
  }
  if(isinview(x-1,y-1)){
    mvwaddch(win, y - cellheigth, x - 1, corner);
  }
  if(isinview(x+1,y-1)){
    mvwaddch(win, y - cellheigth, x + cellwidth, corner);
  }
  if(isinview(x,y+1)){
    mvwhline(win, y + 1, x, horizontal, cellwidth);
  }
  if(isinview(x,y-1)){
    mvwhline(win, y - cellheigth, x, horizontal, cellwidth);
  }
  if(isinview(x-1,y)){
    mvwvline(win, y, x - 1, vertical, cellheigth);
  }
  if(isinview(x+1,y)){
    mvwvline(win, y, x + cellwidth, vertical, cellheigth);
  }

  wmove(win,y,x);
  wrefresh(win);
}

//moves cursor to other cell
void SheetView::RefreshSheet(WINDOW* win, int x, int y)
{
  werase(win); //clear window
  RowCol(win); //add rows and columns
  FillSheet(win); //add current sheet data

  if (x >= 0 && x < cols && y >= 0 && y < lines) {
    address->init(x,y); //change address of cursor
  }//check whether coordinates are in the view
  CreateCursor(win); //place cursor
}

//Initialize window
void SheetView::Display()
{
  int ch, x, y;

  initscr(); //start of ncurses

  //create a new window
  WINDOW *win = newwin(cellheigth*(lines+1), cellwidth*(cols+1), 0, 0);
  keypad(win, TRUE); //enable keyboard inputs

  attr_t old_attr; //remember parameters
  short old_pair;
  wattr_get(win, &old_attr, &old_pair, NULL);

  RefreshSheet(win,0,0);

  wattr_set(win, old_attr, old_pair, NULL); //reset previous parameters

  while ((ch = wgetch(win)) != 'q'){
    int* coords = address->givecoords();
    x = coords[0];
    y = coords[1];
    switch (ch) {
      case KEY_UP:
        RefreshSheet(win, x, y-1);
      break;
      case KEY_RIGHT:
        RefreshSheet(win, x+1, y);
      break;
      case KEY_DOWN:
        RefreshSheet(win, x, y+1);
      break;
      case KEY_LEFT:
        RefreshSheet(win, x-1, y);
      break;
      case '\n':
        RefreshSheet(win, x, y);
      break;
    }//moves the cursor around
  }//wait for an ENTER-input

  delwin(win); //delete window
  endwin(); //end of ncurses
}//Display
