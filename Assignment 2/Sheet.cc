#ifndef __SHT_CC__
#define __SHT_CC__

#include <iostream>
#include "Sheet.h"

//*****************************************************************************

Sheet::Sheet (int width, int height) : width(width),
                                       height(height)
{
  for(int i = 0; i < width; i++)
    sheet.push_back(new Column(height));
}

//*****************************************************************************

Sheet::~Sheet ()
{
  for(int i = 0; i < width; i++)
  {
    delete sheet.back();
    sheet.pop_back();
  }
}

//*****************************************************************************

Cell* Sheet::GetCell (int x, int y)
{
  if (x < width && x >= 0)
    return sheet[x]->GetCell(y);
  return nullptr;
}

//*****************************************************************************

Cell* Sheet::Begin ()
{
  if (width > 0)
    return sheet[0]->Begin();
  return nullptr;
}

//*****************************************************************************

Cell* Sheet::End ()
{
  if (width > 0)
    return sheet[width-1]->End();
  return nullptr;
}

//*****************************************************************************

#endif
