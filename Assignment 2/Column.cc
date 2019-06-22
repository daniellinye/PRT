// Implementatie van standaard functies.

#ifndef __COL_CC__
#define __COL_CC__

#include <iostream>
#include "Column.h"

//*****************************************************************************

Column::Column (int height) : height(height)
{
	for(int i = 0; i < height; i++)
		column.push_back(new Cell());
}

//*****************************************************************************

Column::~Column ()
{
	for(int i = 0; i < height; i++)
  {
    delete column.back();
    column.pop_back();
  }
}

//*****************************************************************************

Cell* Column::GetCell (int index)
{
  if (index < height && index >= 0)
    return column[index];
  return nullptr;
}

//*****************************************************************************

Cell* Column::Begin ()
{
  if (height > 0)
    return column[0];
  return nullptr;
}

//*****************************************************************************

Cell* Column::End ()
{
  if (height > 0)
    return column[height-1];
  return nullptr;
}

//*****************************************************************************

#endif
