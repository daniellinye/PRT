#include "SheetView.h"
#include <ncurses.h>

//*****************************************************
//Sheetview

//constructor
SheetView::SheetView()
{
  lines = 24;
  cols = 80;
  r = Range();
  matrix = new Sheet(lines, cols);
  r.initm(matrix);
  address = new CellAddress();
}

//check whether cell is in view
bool SheetView::isinview(int x, int y)
{
  if (x >= cellwidth && x < (cols + 1) * cellwidth){
    if (y >= cellheigth && y < (lines + 1) * cellheigth){
      return true;
    }
  }
  return false;
}//isinview

//add row and column names
void SheetView::RowCol(WINDOW *win)
{
  int i,n,temp1;
  float temp2;
  char cell[cellwidth] = {0};

  wattron(win, A_STANDOUT);

  //add rownumbers
  for (i = 1; i <= lines; i++) {
    wmove(win, cellheigth * i, 0);
    sprintf(cell,"   %d",i);     //sprintf places the number after a few spaces
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
    }                                 //after 'Z' it counts further from 'AA'

    temp1 = i;
    temp2 = i;
    n = 0;

    while (temp1 > 26) {
      temp1 /= 26;
      temp2 /= 26;
    }

    while (temp1 > 0){
      cell[n+2] = temp1 + 'A' - 1;
      temp2 -= temp1;
      temp1 = round(temp2 * 26);    //round makes sure that the inaccuracy
      n++;                          //of a float is rounded up right
    }
    waddstr(win, cell);
  }
  wattroff(win, A_STANDOUT);
}//RowCol

//print cell
void SheetView::PrintCell(WINDOW* win, int x, int y)
{
  std::stringstream ss = r.getCell(x,y)->giveref()->print();
  std::string str = ss.str();           //convert stringstream to string

  const char* cell = str.c_str();       //convert string to const char*

  x = cellwidth*(x + 1);
  y = cellheigth*(y + 1);

  mvwhline(win, y, x, ' ', cellwidth);  // first empties the cell
  mvwaddstr(win, y, x, cell);           // by placing spaces
}//PrintCell

//implement all cells from Sheet
void SheetView::FillSheet(WINDOW *win)
{
  int x,y;
  for (x = 0; x < cols; x++) {
    for (y = 0; y < lines; y++) {
      PrintCell(win,x,y);
    }
  }
}//FillSheet

//Creates a border for editing
void SheetView::CreateBorder (WINDOW* win)
{
  int x = cellwidth*(address->givex() + 1);
  int y = cellheigth*(address->givey() + 1);
  char corner = '+', vertical = '|', horizontal = '-';

  if(isinview(x-1,y+1)){                    //first checks whether the character(s)
    mvwaddch(win, y + 1, x - 1, corner);    //to be placed is/are in the view and
  }                                         //then adds that/those character(s)
  if(isinview(x+1,y+1)){
    mvwaddch(win, y + 1, x + editwidth, corner);
  }
  if(isinview(x-1,y-1)){
    mvwaddch(win, y - cellheigth, x - 1, corner);
  }
  if(isinview(x+1,y-1)){
    mvwaddch(win, y - cellheigth, x + editwidth, corner);
  }
  if(isinview(x,y+1)){
    mvwhline(win, y + 1, x, horizontal, editwidth);
  }
  if(isinview(x,y-1)){
    mvwhline(win, y - cellheigth, x, horizontal, editwidth);
  }
  if(isinview(x-1,y)){
    mvwvline(win, y, x - 1, vertical, cellheigth);
  }
  if(isinview(x+1,y)){
    mvwvline(win, y, x + editwidth, vertical, cellheigth);
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
  wattron(win, A_STANDOUT);

  if (x >= 0 && x < cols && y >= 0 && y < lines) {
    address->init(x,y); //change address of cursor
  }//check whether coordinates are in the view

  PrintCell(win,address->givex(),address->givey());
  wattroff(win, A_STANDOUT);
  curs_set(0);
  wrefresh(win);

}

void SheetView::StartEdit(WINDOW* win, int x, int y)
{
  int ch, n, i = 0;
  char* cell = new char;

  curs_set(1);

  //subwindow
  WINDOW* edit = subwin(win,cellheigth,editwidth,(y+1)*cellheigth,(x+1)*cellwidth);
  keypad(edit, TRUE); //enable keyboard inputs for the subwindow
  werase(edit);       //clear window
  CreateBorder(win);  //add border around edit window

  noecho();                               //the character to be typed will first
  while((ch = wgetch(edit)) != '\n') {    //be placed in an array, then that array
    noecho();                             //is printed with every new character
    switch (ch) {
      case KEY_BACKSPACE:   //backspace
        if (i > 0) {
          i--;
          for (n = i; n < editwidth - 1; n++) {
            cell[n] = cell[n+1];
          }
          cell[editwidth-1] = ' ';
        }
      break;
      case KEY_DC:          //delete
        for (n = i; n < editwidth - 1; n++) {
          cell[n] = cell[n+1];
        }
        cell[editwidth-1] = ' ';
      break;
      case KEY_LEFT:        //left
        i--;
      break;
      case KEY_RIGHT:       //right
        i++;
      break;
      default:              //normal typing keys
        if (!(has_key(ch))) {
          cell[i] = ch;
          i++;
        }
      break;
    }

    if (i < 0) {
      i++;                    //helps to stay within the range of the edit window
    }
    if (i >= editwidth) {
      for (n = i - editwidth; n < i; n++) {
        mvwaddch(edit,0,n - i + editwidth,cell[n]);       //displays the just typed array
      }
    }
    else {
      mvwaddnstr(edit,0,0,cell,editwidth);
    }
    wmove(edit,0,i);
    wrefresh(edit);
  }

  cell[i] = '\0';

  matrix->replaceCell(x,y,cell); //replaces the cellvalue

  RefreshSheet(win,x,y);
}

//Initialize window
void SheetView::Display()
{
  int ch, x, y;

  initscr(); //start of ncurses

  //create a new window
  WINDOW *win = newwin(cellheigth*(lines+1), cellwidth*(cols+1), 0, 0);
  keypad(win, TRUE); //enable keyboard inputs

  RefreshSheet(win,0,0);

  noecho();                                         //keyboard inputs do not
  while ((ch = wgetch(win)) != 'q' && ch != 'Q'){   //need to be displayed
    noecho();
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
        StartEdit(win,x,y);
      break;
    }//moves the cursor around
  }//wait for an ENTER-input

  delwin(win); //delete window
  endwin(); //end of ncurses
}//Display
