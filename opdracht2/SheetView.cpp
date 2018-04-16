
#include "Range.cpp"
#include <ncurses.h>

static const int lines(24);
static const int cols(80);
static const int cellheigth(1);
static const int cellwidth(8);

class SheetView
{
private:
  Range r;

public:
  SheetView() {
    this->r = Range();
    Sheet* matrix = new Sheet(lines, cols);
    r.initm(matrix);
  };

  //add row and column names
  virtual void RowCol(WINDOW *win){
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
  }

  //TODO: implement all cells from Sheet.cpp
  virtual void FillSheet(WINDOW *win){
    int x,y;
    float value = 1;
    char cell[cellwidth];
    for (y = 0; y < 24; y++) {
      value = r.getCell(0,y)->convertfloat();
      sprintf(cell,"%f",value);
      wmove(win, y + 1, x + 1);
      waddstr(win, cell);
    }
  }

  //Initialize window
	virtual void Display(){
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
  }
};
