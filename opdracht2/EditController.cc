#ifndef __EDC_CC__
#define __EDC_CC__

#include <iostream>
#include "EditController.h"

//*****************************************************************************

EditController::EditController(int x, int y, char *cellvalue) : value(cellvalue)
{
  length = strlen(cellvalue);
  curs_pos = length;
  view = new EditView(x,y);

} // constructor

//*****************************************************************************

EditController::~EditController()
{
  delete view;
} // destructor

//*****************************************************************************

void EditController::EditLoop()
{
  int ch;
  view->Refresh(value,curs_pos);
  do
  {
    noecho();
    switch (ch)
    {
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
        PutChar(ch);
      break;
    } // switch
    view->Refresh(value,curs_pos);
  } while ((ch = view->GetChar()) != '\n');
} // EditLoop

//*****************************************************************************

CellValueBase *EditController::CellValueFactory ()
{
  int type = 0;
  int i = 0;

  if (length == 0)
    return nullptr;

  //if (value[0] == '=')
  //  return new CellFormula();

  if (value[i] == '-')
    i++;

  for (; i < length; i++)
  {
    if (type < 2 && (value[i] == '.' || value[i] == ','))
      type++;
    else if (value[i] < '0' || value[i] > '9')
      type = 2;
  }

  switch (type) {
    case 0:  return new CellValue<int>(atoi(value));
    break;
    case 1:  return new CellValue<float>(atof(value));
    break;
    case 2:  return new CellValue<std::string>(value);
    break;
    default: return nullptr;
  }
}

//*****************************************************************************

void EditController::Backspace()
{
  if (curs_pos > 0)
  {
    length--;
    curs_pos--;
    for (int i = curs_pos; i < length; i++)
      value[i] = value[i+1];

    value[length] = '\0';
  } // if
} // Backspace

//*****************************************************************************

void EditController::Delete()
{
  if (curs_pos < length)
  {
    length--;
    for (int i = curs_pos; i < length; i++)
      value[i] = value[i+1];

    value[length] = '\0';
  } // if
} // Delete

//*****************************************************************************

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

//*****************************************************************************

void EditController::PutChar(int ch)
{
  if (!has_key(ch))
  {
    for (int i = length; i > curs_pos; i--)
      value[i] = value[i-1];

    value[curs_pos] = ch;
    curs_pos++;
    length++;
    value[length] = '\0';
  } // if
} // PutChar

//*****************************************************************************

#endif
