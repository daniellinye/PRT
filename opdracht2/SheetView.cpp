#include "SheetView.h"
#include <ncurses.h>
#include <string>

//*****************************************************
//Sheetview

//constructor
SheetView::SheetView()
{
  initscr();                //start of ncurses

  lines = 24;
  cols = 80;

  sheet = new Sheet(lines, cols);
  address = new CellAddress();

  CreateWindow();
  initView();
  RefreshSheet();

  keypad(stdscr, TRUE);     // enable keyboard inputs
  curs_set(0);
} // SheetView


//destructor
SheetView::~SheetView()
{
  delete sheet;
  delete address;

  delwin(window); //delete window
  delwin(stdscr); //delete stdscr
  endwin();       //end of ncurses
} // ~SheetView

// Fetch a single character from the window
int SheetView::getchar()
{
  noecho();
  return getch();
} // getchar


// moves cursor to other cell
void SheetView::Move(int input)
{
  int x,y;
  address->givecoords(x,y);

  switch (input)
  {
    case KEY_UP:
      if (y > 0)
        y--;
    break;
    case KEY_RIGHT:
      if (x < maxcols - 1)
        x++;
    break;
    case KEY_DOWN:
      if (y < maxlines - 1)
        y++;
    break;
    case KEY_LEFT:
      if (x > 0)
        x--;
    break;
  }

  address->init(x,y);
  RefreshSheet();
} // Move


// Delete value in selected cell
void SheetView::Delete()
{
  int x,y;
  address->givecoords(x,y);
  sheet->replaceCell(x,y,"");
} // Delete


// Creates an edit window
void SheetView::initEdit()
{
  int x,y;
  char *cellvalue;
  EditController *edit;

  address->givecoords(x,y);

  cellvalue = const_cast<char*>(sheet->getCell(x,y)->giveref()->print().str().c_str());
  edit = new EditController(x,y,cellvalue);

  CreateBorder();
  edit->EditLoop();
  RefreshSheet();

  delete edit;
}


// Create window
void SheetView::CreateWindow()
{
  int scrheight,scrwidth;
  getmaxyx(stdscr,scrheight,scrwidth);

  maxcols = (scrwidth / cellwidth) - 1;     // sets maximum amount
  maxlines = (scrheight / cellheight) - 1;  // of lines and columns

  window = subwin(stdscr,scrheight - cellheight, scrwidth - cellwidth, cellheight, cellwidth);
}


// Add rows and colums
void SheetView::initView()
{
  const int letters = 'Z' - 'A' + 1;
  char* colname = new char[cellwidth - 1];
  short aantalletters;
  float hulpflt;
  int letteri;

  attron(A_STANDOUT);             // Row -and collumn names are printed black on white

  //add column names
  for (int i = 0; i < cols && i < maxcols; i++)
  {
    aantalletters = 1;
    hulpflt = i;
    letteri = 0;
    while (hulpflt >= letters)
    {
      hulpflt = hulpflt / letters - 1;
      aantalletters++;
    }
    while (letteri < aantalletters)
    {
      colname[letteri] = 'A' + hulpflt;
      hulpflt = (hulpflt - (int) hulpflt) * letters;
      letteri++;
    }
    colname[letteri] = '\0';
    mvprintw(0,cellwidth * (i + 1),"   %*s",3 - cellwidth,colname);
  }

  //add rownumbers
  for (int i = 1; i <= lines && i <= maxlines; i++)
  {
    mvprintw(cellheight * i, 0,"%*d   ",cellwidth - 3,i);
  }

  attroff(A_STANDOUT);
  delete[] colname;
} // initView


// Refreshes the window to the sheet
void SheetView::RefreshSheet()
{
  int x,y;
  const char* cellvalue;

  werase(window);

  for (x = 0; x < cols && x < maxcols; x++)
    for (y = 0; y < lines && y < maxlines; y++){
      PrintCell(x,y);
    }

  address->givecoords(x,y);
  cellvalue = sheet->getCell(x,y)->giveref()->print().str().c_str();

  wattron(window,A_STANDOUT);
  mvwprintw(window,cellheight * y,cellwidth * x,"%*s",cellwidth,cellvalue);
  wattroff(window,A_STANDOUT);

  wrefresh(window);
} // RefreshSheet


// prints cell
void SheetView::PrintCell(int x, int y)
{
  const char* cellvalue = sheet->getCell(x,y)->giveref()->print().str().c_str();
  mvwprintw(window,cellheight * y,cellwidth * x,"%.*s",cellwidth,cellvalue);
}//PrintCell


void SheetView::CreateBorder()
{
  int x,y;
  char corner = '+', vertical = '|', horizontal = '-';

  address->givecoords(x,y);

  if(x > 0 && y > 0){
    mvwaddch(window, (cellheight * y) - 1, (cellwidth * x) - 1, corner);
  }
  if(x < maxcols && x < cols && y > 0){
    mvwaddch(window, (cellheight * y) - 1, cellwidth * (x + 1), corner);
  }
  if(x > 0 && y < maxlines && y < lines){
    mvwaddch(window, cellheight * (y + 1), (cellwidth * x) - 1, corner);
  }
  if(x < maxcols && x < cols && y < maxlines && y < lines){
    mvwaddch(window, cellheight * (y + 1), cellwidth * (x + 1), corner);
  }
  if(y > 0){
    mvwhline(window, (cellheight * y) - 1, cellwidth * x, horizontal, cellwidth);
  }
  if(y < maxlines && y < lines){
    mvwhline(window, cellheight * (y + 1), cellwidth * x, horizontal, cellwidth);
  }
  if(x > 0){
    mvwvline(window, cellheight * y, (cellwidth * x) - 1, vertical, cellheight);
  }
  if(x < maxcols && x < cols){
    mvwvline(window, cellheight * y, cellwidth * (x + 1), vertical, cellheight);
  }
  wrefresh(window);
}


//*****************************************************
//SheetController

SheetController::SheetController()
{
  view = new SheetView();
}

SheetController::~SheetController()
{
  delete view;
}

void SheetController::MainLoop()
{
  int input;

  while ((input = view->getchar()) != 'q' && input != 'Q')
  {
    switch (input)
    {
      case KEY_UP: case KEY_RIGHT:
      case KEY_DOWN: case KEY_LEFT:
        view->Move(input);
      break;
      case KEY_BACKSPACE: case KEY_DC:
        view->Delete();
      break;
      case 'r': case 'R':
        //view.ResizeSheet(win);
      break;
      case KEY_ENTER: case '\n':
        view->initEdit();
      break;
    }//moves the cursor around
  }
}


//*****************************************************
//EditView

EditView::EditView(int x, int y)
{
  window = subwin(stdscr,cellheight,cellwidth,cellheight*(y+1),cellwidth*(x+1));
  keypad(window, TRUE);     // enable keyboard inputs
  curs_set(1);
  werase(window);
} // constructor


EditView::~EditView()
{
  delwin(window);
  curs_set(0);
} // destructor


//Refreshes the editwindow
void EditView::Refresh()
{
  mvwprintw(window,0,0,"");
  wrefresh(window);
}

// Fetch a single character from the window
int EditView::getchar()
{
  noecho();
  return getch();
} // getchar


//*****************************************************
//EditController

EditController::EditController(int x, int y, char *cellvalue)
{
  newValue = cellvalue;
  view = new EditView(x,y);
  length = strlen(newValue);
  curs_pos = length;
} // constructor


EditController::~EditController()
{
  delete view;
} // destructor


void EditController::EditLoop()
{
  int ch;

  noecho();
  do
  {
    noecho();
    view->Refresh();
    switch (ch) {
      case KEY_BACKSPACE:   //backspace
        Backspace();
      break;
      case KEY_DC:          //delete
        Delete();
      break;
      case KEY_LEFT:        //left
        Left();
      break;
      case KEY_RIGHT:       //right
        Right();
      break;
      default:              //normal typing keys
        Putchar(ch);
      break;
    }
  } while((ch = view->getchar()) != '\n');
} // EditLoop


void EditController::Backspace()
{
  if (curs_pos > 0)
  {
    length--;
    curs_pos--;
    for (int i = curs_pos; i < length; i++)
    {
      newValue[i] = newValue[i+1];
    }
    newValue[length] = '\0';
  }
} // Backspace


void EditController::Delete()
{
  if (curs_pos < length)
  {
    length--;
    for (int i = curs_pos; i < length; i++)
    {
      newValue[i] = newValue[i+1];
    }
    newValue[length] = '\0';
  }
} // Delete


void EditController::Left()
{
  if (curs_pos > 0)
    curs_pos--;
} // Left


void EditController::Right()
{
  if (curs_pos < length)
    curs_pos++;
} // Right


void EditController::Putchar(int ch)
{
  for (int i = length; i > curs_pos; i--)
  {
    newValue[i] = newValue[i-1];
  }
  newValue[curs_pos] = ch;
  curs_pos++;
  length++;
  newValue[length] = '\0';
} // Putchar
