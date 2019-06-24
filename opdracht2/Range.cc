#ifndef __RNG_CC__
#define __RNG_CC__

#include <iostream>
#include "Range.h"

//*****************************************************************************

Range::Range (Sheet* sheet,std::string range) : sheet(sheet)
{
  b = new CellAddress();
  e = new CellAddress();
  ParseString(range);
} 

//*****************************************************************************

Range::Range (Sheet* sheet,CellAddress *b, CellAddress *e) : b(b),
                                                                   e(e)
{

}

//*****************************************************************************

Range::~Range ()
{
  delete b;
  delete e;
}

//*****************************************************************************

void Range::ParseString (std::string range)
{
  int i = 0, temp = 0;
  std::string coordinate = "";

  for (; range[i] != ':'; i++)
    coordinate += range[i];

  if (!b->CreateFromReference(coordinate))
    b = nullptr;

  coordinate = "";
  i++;

  for (; range[i] != '\0'; i++)
    coordinate += range[i];

  if (!e->CreateFromReference(coordinate))
    e = nullptr;
  
  //check if coordinates are reversed
  if(e->x > b->x || (e->x == b->x && b->y < e->y))
  {
    temp = e->x;
    i = e->y;
    e->x = b->x;
    e->y = b->y;
    b->x = temp;
    b->y = i;
  }
}

//*****************************************************************************

Cell* Range::getValue(const int x, const int y)
{
  return sheet->GetCell(x, y);
}

//*****************************************************************************

RangeIterator Range::begin(void)
{
  return RangeIterator(*this, b->x, b->y);
}

//*****************************************************************************

RangeIterator Range::end(void)
{
  return RangeIterator(*this, e->x, e->y);
}

//*****************************************************************************

RangeIterator::RangeIterator(Range &range, int x, int y) : range(range), 
                                                                 x(x), 
                                                                 y(y)
{
  
}

//*****************************************************************************

#endif
