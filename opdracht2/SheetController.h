#ifndef __SHC_H__
#define __SHC_H__

#include <iostream>
#include <ncurses.h>
#include "SheetView.h"


class CellFormula;

class SheetController
{
  public:
    //Constructor
    SheetController(void);

    //Destructor
    ~SheetController(void);

    //De main loop
    void MainLoop(void);

  private:
    SheetView *view;
};

#endif
