#ifndef __CV_H__
#define __CV_H__

#include <sstream>
#include "CellValueBase.h"

template <typename T>
class CellValue : public CellValueBase
{
  public:

    //*****************************************************************************

    CellValue (T value) : CellValueBase(),
                          value(value)
    {

    }

    //*****************************************************************************

    ~CellValue ()
    {

    }

    //*****************************************************************************

    void SetValue (T newvalue)
    {
      value = newvalue;
    }

    //*****************************************************************************

    std::string GetLiteral ()
    {
      std::stringstream ss;
      ss << value;
      return ss.str();
    }

    //*****************************************************************************

    std::string GetString ()
    {
      std::stringstream ss;
      ss << value;
      return ss.str();
    }

    //*****************************************************************************

    float GetFloat ()
    {
      std::stringstream ss;
      float output;

      ss << value;
      if (!(ss >> output))
        return 0;

      return output;
    }

    //*****************************************************************************

  private:
    T value;
};

#endif
