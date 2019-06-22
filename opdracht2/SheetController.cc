#ifndef __SHC_CC__
#define __SHC_CC__

#include "SheetController.h"
#include <string>

//*****************************************************************************
//SheetController

SheetController::SheetController()
{
  view = new SheetView();
} // constructor

//*****************************************************************************

SheetController::~SheetController()
{
  delete view;
} // destructor

//*****************************************************************************

void SheetController::MainLoop()
{
  int input;

  while ((input = view->GetChar()) != 'q' && input != 'Q')
  {
    switch (input)
    {
      case KEY_UP: case KEY_RIGHT:
      case KEY_DOWN: case KEY_LEFT:
        view->Move(input);
      break;
      case KEY_BACKSPACE: case KEY_DC:
      case KEY_CLEAR: case KEY_DL:
      case 0x7f:
        view->Delete();
      break;
      case 's': case 'S':
        //Save();
      break;
      case 'l': case 'L':
        //Load();
      break;
      case KEY_ENTER: case '\n':
      case '\r':
        view->InitEdit();
      break;
    } // switch
  } // while
} // MainLoop

//*****************************************************************************

#endif
