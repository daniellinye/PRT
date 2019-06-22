#ifndef __CELL_H__
#define __CELL_H__

#include <memory>
#include "CellValue.h"

class Cell
{
  public:
    Cell (void);
    ~Cell (void);

    void Empty(void);
    void SetValue(CellValueBase*);
    std::string GetValue(void);

  private:
    std::unique_ptr<CellValueBase> value;
};

#endif
