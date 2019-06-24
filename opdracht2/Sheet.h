#ifndef __SHT_H__
#define __SHT_H__

#include <vector>
#include "Column.h"

class Sheet
{
  public:
  	Sheet(int,int);
  	~Sheet(void);

  	Cell* GetCell(int,int);
  	Cell* Begin(void);
  	Cell* End(void);

  private:
  	std::vector<Column*> sheet;
  	int width;
    int height;
};

#endif
