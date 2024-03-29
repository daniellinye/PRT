

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
    float calc = 0;
    //TODO: float berekenen en in string zetten
    for(; value[i] != '(' && i < size; i++)
    {
        type += value[i];
    }

    Range range = Range(sheet, value);

    i = 0; size = 0;

    if(type == "SUM" || type == "AVG" || type == "COUNT")

    for(auto it : range)
    {
        if(it->GetLiteral() != "")
            i++;
        try
        {
            atoi(it->GetLiteral().c_str());
            if(it->GetLiteral().find('.') == std::string::npos && it->GetLiteral() != "")
                size++;
        } catch(int j) { }
        calc += it->GetFloat();
    }

    if(type == "SUM")
    {
        return std::to_string(calc) ;
    }
    else if(type == "AVG")
    {   
        if(i > 0)
            return std::to_string((float)(calc/(i)));
    }
    else if(type == "COUNT")
    {
        return std::to_string(size);
    }

    return "ERR";
}

float CellFormula::GetFloat()
{
    //TODO: in float neerzetten na berekenen
    return 0;
}



 #endif