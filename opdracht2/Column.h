#ifndef __COL_H__
#define __COL_H__

#include <vector>
#include "Cell.h"

class Column
{
  public:
  	Column(int);
  	~Column(void);

  	Cell* GetCell(int);
  	Cell* Begin(void);
  	Cell* End(void);

  private:
  	std::vector<Cell*> column;
  	int height;
};

#endif
