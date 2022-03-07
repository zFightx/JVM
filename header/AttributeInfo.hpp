#ifndef __AttributeInfo_HPP__
#define __AttributeInfo_HPP__

#include "Dados.hpp"

class AttributeInfo
{
    private:
        u2 attribute_name_index;
        u4 attribute_length;
        u1 *info;
    public:
        AttributeInfo();
};


#endif