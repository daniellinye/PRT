

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
    //TODO: float berekenen en in string zetten
    return "";
}

float CellFormula::GetFloat()
{
    //TODO: in float neerzetten na berekenen
    return 0;
}



 #endif