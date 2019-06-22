#ifndef __RNG_H__
#define __RNG_H__

#include <iterator>
#include "Sheet.h"
#include "CellAddress.h"

class Range
{
  public:
    Range (Sheet*,std::string);
    Range (Sheet*,CellAddress*, CellAddress*);
    ~Range (void);

    void ParseString (std::string);

  private:
    Sheet *sheet;
    CellAddress *begin;
    CellAddress *end;
};

#endif
