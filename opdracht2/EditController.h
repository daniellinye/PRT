#ifndef __EDC_H__
#define __EDC_H__

#include "SheetView.h"
#include "EditView.h"

class EditController
{
  public:
    //Constructor
    EditController(int,int,char*);

    //Destructor
    ~EditController(void);

    //Loop voor het aanpassen van de cellValue
    void EditLoop(void);

    CellValueBase *CellValueFactory (void);

  private:
    void Backspace();
    void Delete();
    void Left();
    void Right();
    void PutChar(int);

    EditView *view;
    char *value;
    int length, curs_pos;
};

#endif
