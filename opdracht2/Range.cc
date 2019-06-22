#ifndef __RNG_CC__
#define __RNG_CC__

#include <iostream>
#include "Range.h"

//*****************************************************************************

Range::Range (Sheet* sheet,std::string range) : sheet(sheet)
{
  begin = new CellAddress();
  end = new CellAddress();
  ParseString(range);
}

//*****************************************************************************

Range::Range (Sheet* sheet,CellAddress *begin, CellAddress *end) : begin(begin),
                                                                   end(end)
{

}

//*****************************************************************************

Range::~Range ()
{
  delete begin;
  delete end;
}

//*****************************************************************************

void Range::ParseString (std::string range)
{
  int i = 2;
  std::string coordinate = "";

  for (; range[i] != ':'; i++)
    coordinate += range[i];

  if (!begin->CreateFromReference(coordinate))
    begin = nullptr;

  coordinate = "";
  i++;

  for (; range[i] != ')'; i++)
    coordinate += range[i];

  if (!end->CreateFromReference(coordinate))
    end = nullptr;
}

//*****************************************************************************

#endif
