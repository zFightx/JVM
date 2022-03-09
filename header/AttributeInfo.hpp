#ifndef __AttributeInfo_HPP__
#define __AttributeInfo_HPP__

#include "Dados.hpp"

class AttributeInfo
{
    public:
        u2 attribute_name_index;
        u4 attribute_length;
        union{

        } info;
        AttributeInfo();
};


#endif