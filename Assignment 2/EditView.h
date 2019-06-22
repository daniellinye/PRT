#ifndef __EDV_H__
#define __EDV_H__

#include <ncurses.h>

class EditView
{
  public:
    //Constructor
    EditView(int,int);

    //Destructor
    ~EditView(void);

    //Refreshes the editing window
    void Refresh(char*,int);

    //Asks for input and returns char
    int GetChar(void);

  private:
    WINDOW *window;               // pointer to the editwindow
    int tracker;                  // keeps track of visible chars
};

#endif
