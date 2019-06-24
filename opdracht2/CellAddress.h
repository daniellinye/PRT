#ifndef __CA_H__
#define __CA_H__

class CellAddress
{
  public:
  	CellAddress (void);
    CellAddress (int,int);
    CellAddress (std::string);

    ~CellAddress (void);

    void SetAddress (int,int);
    bool CreateFromReference (std::string);

    int x;
    int y;

  private:
};

#endif
