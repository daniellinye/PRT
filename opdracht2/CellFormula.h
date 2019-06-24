#ifndef __CVF_H__
#define __CVF_H__

#include<string>
#include "CellValueBase.h"
#include "Range.h"

class Sheet;

class CellFormula : public CellValueBase
{
  public:

    CellFormula (std::string value, Sheet *sheet);

    ~CellFormula ();

    void SetValue (std::string newvalue);

    std::string GetLiteral ();

    std::string GetString ();

    float GetFloat ();

  private:
    std::string value;
    Sheet *sheet;
};

#endif
