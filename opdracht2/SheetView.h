#include <iostream>
#include "Range.h"
#include <ncurses.h>
#include <string.h>

using namespace std;

static const int cellheight(1); //height of a single cell
static const int cellwidth(8);  //width of a single cell
static const int editwidth(16); //width of two cells, for editing window

class SheetView
{
  public:
    //Constructor
    SheetView();

    //Destructor
    ~SheetView();

    //Asks for input and returns char
    int getchar();

    //Move cursorposition in window
    void Move(int);

    //Empty selected cell
    void Delete();

    //Start editing the selected cell
    void initEdit();

  private:
    //Create the main window
    void CreateWindow();

    //Refresh the main window and display the sheet
    void RefreshSheet();

    //initiate the view with row -and columnnumbers
    void initView();

    //print cell at coordinate (x,y)
    void PrintCell(int,int);

    //Creates a border around the editwindow
    void CreateBorder();

    int maxlines, maxcols;        // maximum amount of lines and columns that fit the screen
    int lines, cols;              // amount of lines and columns
    Sheet* sheet;                 // pointer to a Sheet
    CellAddress* address;         // pointer to a CellAddress
    WINDOW *window;               // pointer to the window
};


class SheetController
{
  public:
    //Constructor
    SheetController();

    //Destructor
    ~SheetController();

    //De main loop
    void MainLoop();

  private:
    SheetView *view;
};


class EditView
{
  public:
    //Constructor
    EditView(int,int);

    //Destructor
    ~EditView();

    //Refreshes the editing window
    void Refresh(char*,int);

    //Asks for input and returns char
    int getchar();

  private:
    WINDOW *window;               // pointer to the editwindow
    int tracker;                  // keeps track of visible chars
};


class EditController
{
  public:
    //Constructor
    EditController(int,int,char*);

    //Destructor
    ~EditController();

    //Loop voor het aanpassen van de cellValue
    void EditLoop();

  private:
    void Backspace();
    void Delete();
    void Left();
    void Right();
    void Putchar(int);


    EditView *view;
    char *newValue;
    int length, curs_pos;
};
