#ifndef __CELL_CC__
#define __CELL_CC__

#include <iostream>
#include "Cell.h"

//*****************************************************************************

Cell::Cell ()
{
  value = nullptr;
}

//*****************************************************************************

Cell::~Cell ()
{

}

//*****************************************************************************

void Cell::Empty()
{
  value.reset(nullptr);
}

//*****************************************************************************

void Cell::SetValue(CellValueBase *newvalue)
{
  value.reset(newvalue);
}

//*****************************************************************************

std::string Cell::GetValue()
{
  if (value != nullptr)
    return value->GetString();
  return "";
}

//*****************************************************************************

float Cell::GetFloat()
{
  if (value != nullptr)
    return value->GetFloat();
  return 0;
}

//*****************************************************************************

std::string Cell::GetLiteral()
{
  if (value != nullptr)
    return value->GetLiteral();
  return "";
}

//*****************************************************************************

#endif
