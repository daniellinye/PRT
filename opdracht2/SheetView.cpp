#include "SheetView.h"
#include <ncurses.h>
#include <cstring>

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

void SheetView::GetUserInput(WINDOW* edit, char* input)
{
  unsigned int i = 0, n;
  int ch;
  werase(edit);
  wrefresh(edit);
  noecho();                                 //the character to be typed will first
  while((ch = wgetch(edit)) != '\n') {      //be placed in an array, then that array
    noecho();                               //is printed with every new character
    switch (ch) {
      case KEY_BACKSPACE:   //backspace
        if (i > 0) {
          i--;
          for (n = i; n < strlen(input) - 1; n++) {
            input[n] = input[n+1];
          }
          input[strlen(input)-1] = '\0';
        }
      break;
      case KEY_DC:          //delete
        for (n = i; n < strlen(input) - 1; n++) {
          input[n] = input[n+1];
        }
        input[strlen(input)-1] = '\0';
      break;
      case KEY_LEFT:        //left
      if (i > 0) {
        i--;
      }
      break;
      case KEY_RIGHT:       //right
      if (i < strlen(input)) {
        i++;
      }
      break;
      default:              //normal typing keys
        if (!(has_key(ch))) {
          input[i] = ch;
          i++;
        }
      break;
    }

    if (i < 0) {
      i++;                    //helps to stay within the range of the edit window
    }
    mvwhline(edit,0,0,' ',editwidth);
    if (i >= editwidth) {
      for (n = strlen(input) - editwidth; n < i; n++) {
        mvwaddch(edit,0,n - i + editwidth,input[n]);       //displays the just typed array
      }
    }
    else {
      mvwaddnstr(edit,0,0,input,editwidth);
    }
    wmove(edit,0,i);
    wrefresh(edit);
  }
}

//Creates a border for editing
void SheetView::CreateBorder(WINDOW* win, int height, int width)
{
  int x = cellwidth*(address->givex() + 1);
  int y = cellheigth*(address->givey() + 1);
  char corner = '+', vertical = '|', horizontal = '-';

  if(isinview(x-1,y-1)){                    //first checks whether the character(s)
    mvwaddch(win, y - 1, x - 1, corner);    //to be placed is/are in the view and
  }                                         //then adds that/those character(s)
  if(isinview(x+1,y-1)){
    mvwaddch(win, y - 1, x + width, corner);
  }
  if(isinview(x-1,y+1)){
    mvwaddch(win, y + height, x - 1, corner);
  }
  if(isinview(x+1,y+1)){
    mvwaddch(win, y + height, x + width, corner);
  }
  if(isinview(x,y-1)){
    mvwhline(win, y - 1, x, horizontal, width);
  }
  if(isinview(x,y+1)){
    mvwhline(win, y + height, x, horizontal, width);
  }
  if(isinview(x-1,y)){
    mvwvline(win, y, x - 1, vertical, height);
  }
  if(isinview(x+1,y)){
    mvwvline(win, y, x + width, vertical, height);
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

void SheetView::ResizeSheet(WINDOW* win)
{
  int nwidth = 0, nheight = 0;
  unsigned int i;
  char* input = new char;
  int x = address->givex(), y = address->givey();
  CreateBorder(win,4,editwidth*2);
  mvwaddstr(win,cellheigth*(y+1),cellwidth*(x+1),"Resizing menu");

  //subwindow
  WINDOW* edit = subwin(win,1,editwidth*2,(y+2)*cellheigth + 2,(x+1)*cellwidth);
  keypad(edit, TRUE); //enable keyboard inputs for the subwindow
  werase(edit);       //clear window
  curs_set(1);

  mvwaddstr(win,cellheigth*(y + 1)+2,cellwidth*(x + 1),"Number of rows: ");
  wrefresh(win);
  GetUserInput(edit, input);
  for (i = 0; i < strlen(input); i++) {
    nheight = nheight*10 + input[i] - '0';
  }

  input = new char;

  mvwaddstr(win,cellheigth*(y + 1)+2,cellwidth*(x + 1),"Number of columns: ");
  wrefresh(win);
  GetUserInput(edit, input);
  for (i = 0; i < strlen(input); i++) {
    nwidth = nwidth*10 + (int)input[i] - '0';
  }
  matrix->resize(nheight, nwidth);

  lines = nheight;
  cols = nwidth;
  delete address;
  address = new CellAddress();

  delwin(edit);
  RefreshSheet(win,x,y);
}

void SheetView::StartEdit(WINDOW* win, int x, int y)
{
  bool isafloat = false, isanint = true;
  int intvalue = 0;
  unsigned int n, i;
  char* cell = new char;
  r.getCell(x,y)->giveref()->print() >> cell;
  i = r.getCell(x,y)->giveref()->print().str().size();
  curs_set(1);

  //subwindow
  WINDOW* edit = subwin(win,cellheigth,editwidth,(y+1)*cellheigth,(x+1)*cellwidth);
  keypad(edit, TRUE); //enable keyboard inputs for the subwindow
  werase(edit);       //clear window
  CreateBorder(win, cellheigth, editwidth); //add border around edit window

  if (i >= editwidth) {
    for (n = strlen(cell) - editwidth; n < i; n++) {
      mvwaddch(edit,0,n - i + editwidth,cell[n]); //displays the cellvalue
    }
  }
  else {
    mvwaddnstr(edit,0,0,cell,editwidth);
  }

  GetUserInput(edit, cell);       //fetches user input as char*

  for (n = 0; n < strlen(cell); n++) {
    if (isanint && isdigit(cell[n])) {
      intvalue = intvalue*10 + cell[n] - '0';
      matrix->replaceCell(x,y,intvalue);  //replaces the cellvalue
    }
    if ((isafloat == false && (cell[n] == '.' || cell[n] == ',')) || (isafloat && isdigit(cell[n]))) {
      matrix->replaceCell(x,y,cell);  //replaces the cellvalue
      matrix->getCell(x,y)->giveref()->convertfloat();
      isafloat = true;
      isanint = false;
    } //converts to a float
    else if ((!isanint && !isafloat) || !isdigit(cell[n])) {
      matrix->replaceCell(x,y,cell);  //replaces the cellvalue
      isanint = false;
    }
  }

  delwin(edit);
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
      case KEY_BACKSPACE: case KEY_DC:
        matrix->replaceCell(x,y,"");
        RefreshSheet(win, x, y);
      break;
      case 'R': case 'r':
        ResizeSheet(win);
      break;
      case '\n':
        StartEdit(win,x,y);
      break;
    }//moves the cursor around
  }//wait for an ENTER-input

  delwin(win); //delete window
  endwin(); //end of ncurses
}//Display
