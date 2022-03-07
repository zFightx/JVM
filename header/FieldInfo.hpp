#ifndef __FieldInfo_HPP__
#define __FieldInfo_HPP__

#include "Dados.hpp"
#include "AttributeInfo.hpp"

class FieldInfo
{
    private:
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        AttributeInfo *attributes; 
    public:
        FieldInfo();
};


#endif