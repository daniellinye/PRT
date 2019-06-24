#ifndef __CA_CC__
#define __CA_CC__

#include <iostream>
#include <string>
#include "CellAddress.h"

//*****************************************************************************

CellAddress::CellAddress () : x(0),
                              y(0)
{

}

//*****************************************************************************

CellAddress::CellAddress (int x, int y) : x(x),
                                          y(y)
{

}

//*****************************************************************************

CellAddress::CellAddress (std::string coordinate)
{
  CreateFromReference(coordinate);
}

//*****************************************************************************

CellAddress::~CellAddress ()
{

}

//*****************************************************************************

void CellAddress::SetAddress (int x, int y)
{
  this->x = x;
  this->y = y;
}

//*****************************************************************************

bool CellAddress::CreateFromReference (std::string coordinate)
{
  bool col = false;
  bool row = false;
  x = 0;
  y = 0;

  for (unsigned int i = 0; i < coordinate.length(); i++)
  {
    if (!row && coordinate[i] >= 'A' && coordinate[i] <= 'Z')
    {
      x *= 26;
      x += coordinate[i] - 'A' + 1;
      col = true;
    }
    else if (col && coordinate[i] >= '0' && coordinate[i] <= '9')
    {
      y *= 10;
      y += coordinate[i] - '0';
      row = true;
    }
    else
      return false;
  }

  x--;
  y--;
  return (col && row);
}

//*****************************************************************************

#endif
