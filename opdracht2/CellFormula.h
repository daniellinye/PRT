#ifndef __CVF_H__
#define __CVF_H__

#include<string>
#include "CellValueBase.h"

class CellFormula : public CellValueBase
{
  public:

    CellFormula (std::string value);

    ~CellFormula ();

    void SetValue (std::string newvalue);

    std::string GetLiteral ();

    std::string GetString ();

    float GetFloat ();

  private:
    std::string value;
};

#endif
