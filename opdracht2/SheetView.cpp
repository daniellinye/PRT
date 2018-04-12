
#include <ncurses.h>

class SheetView
{
private:
  int h, b;
public:
  SheetView() {
    this->h = 24;
    this->b = 80;
  };

  virtual int retH () {
    return this->h;
  }

  virtual int retB () {
    return this->b;
  }

	virtual void Display(){
    initscr();

    refresh();

    endwin();
  }
};
