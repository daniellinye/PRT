#ifndef __RNG_H__
#define __RNG_H__

#include <iterator>
#include <vector>
#include "Sheet.h"
#include "CellAddress.h"

class RangeIterator;

class Range
{
  public:
    //stands for "b"egin and "e"nd
    CellAddress *b;
    CellAddress *e;


    Range (Sheet*,std::string);
    Range (Sheet*,CellAddress*, CellAddress*);
    ~Range (void);

    void ParseString (std::string);

    Cell* getValue(const int x, const int y);

    typedef RangeIterator iter;

    RangeIterator begin();
    
    RangeIterator end();

  private:
    Sheet *sheet;

    std::string function, total;
};

class RangeIterator : public std::iterator<std::input_iterator_tag, Cell*>
{
  public:

  RangeIterator(Range &range, int x, int y);

  RangeIterator &operator++()
  {
    if(x < range.e->x)
    {
      x++;
    }
    else if(y < range.e->y)
    {
      y++;
      x = range.b->x;
    }
    return *this;
  }

  private:
    Range &range;
    int x, y;

};

#endif
