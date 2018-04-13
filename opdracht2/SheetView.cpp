
#include "Range.cpp"
#include <ncurses.h>

static const int lines(24);
static const int cols(80);
static const int cellheigth(1);
static const int cellwidth(8);

class SheetView
{
private:
  Range* r;

public:
  SheetView() {
    this->r = new Range();
  };

  virtual void RowCol(WINDOW *win){
    int i,n;
    char cell[8];

    wattron(win, A_STANDOUT);

    for (i = 1; i < lines; i++) {
      wmove(win, cellheigth * i, 0);
      sprintf(cell,"   %d",i);
      for (n = 0; n < cellwidth; n++) {
        if (!cell[n]) {cell[n] = ' ';}
      }
      waddstr(win, cell);
    }

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
  virtual void FillSheet(){


  }

	virtual void Display(){
    int ch;
    initscr();

    WINDOW *win = newwin(cellheigth*lines, cellwidth*cols, 0, 0);
    keypad(win, TRUE); //enable keyboard inputs

    attr_t old_attr; //remember parameters
    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);

    RowCol(win);

    wattr_set(win, old_attr, old_pair, NULL); /* Oude settings terugzetten */
    wrefresh(win);
    while ((ch = wgetch(win)) != '\n');
    delwin(win); /* Dealloceer venster */
    endwin();
  }
};
