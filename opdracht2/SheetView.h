#ifndef __SHV_H__
#define __SHV_H__

#include <ncurses.h>
#include <string.h>

#include "Sheet.h"
#include "CellAddress.h"
#include "EditController.h"

class SheetView
{
  public:
    //Constructor
    SheetView(void);

    //Destructor
    ~SheetView(void);

    //Asks for input and returns char
    int GetChar(void);

    //Move cursorposition in window
    void Move(int);

    //Empty selected cell
    void Delete(void);

    //Start editing the selected cell
    void InitEdit(void);

  private:
    //Create the main window
    void CreateWindow(void);

    //Refresh the main window and display the sheet
    void RefreshSheet(void);

    //initiate the view with row -and columnnumbers
    void InitView(void);

    //print cell at coordinate (x,y)
    void PrintCell(int,int);

    //Creates a border around the editwindow
    void CreateBorder();

    int maxlines, maxcols;        // maximum amount of lines and columns that fit the screen
    Sheet* sheet;                 // pointer to a Sheet
    CellAddress* address;         // pointer to a CellAddress
    WINDOW *window;               // pointer to the window
};

#endif
