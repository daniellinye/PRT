

#ifndef __CVF_CC__
#define __CVF_CC__


 #include <iostream>
 #include "CellFormula.h"


CellFormula::CellFormula(std::string value) : CellValueBase(), 
                            value(value)
{
    
}

CellFormula::~CellFormula() { };

std::string CellFormula::GetLiteral()
{
    return value;
}

std::string CellFormula::GetString()
{
    std::string type = "";
    //TODO: float berekenen en in string zetten
    for(int i = 1; i < 4; i++)
    {
        type += value[i];
    }
    return "";
}

float CellFormula::GetFloat()
{
    //TODO: in float neerzetten na berekenen
    return 0;
}



 #endif