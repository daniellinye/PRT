

#ifndef __CVF_CC__
#define __CVF_CC__


 #include <iostream>
 #include "CellFormula.h"
 



CellFormula::CellFormula(std::string value, Sheet *sheet) : CellValueBase(), 
                            value(value), sheet(sheet)
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
    int i = 1, size = value.size();
    //TODO: float berekenen en in string zetten
    for(; value[i] != '(' && i < size; i++)
    {
        type += value[i];
    }

    Range range = Range(sheet, value);

    for(auto mem : range)
    {
        std::cout << mem->GetFloat() << std::endl;
    }

    return "ERR";
}

float CellFormula::GetFloat()
{
    //TODO: in float neerzetten na berekenen
    return 0;
}



 #endif