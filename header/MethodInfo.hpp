#ifndef __MethodInfo_HPP__
#define __MethodInfo_HPP__

#include "Dados.hpp"
#include "AttributeInfo.hpp"

class MethodInfo
{
    private:
        u2 access_flags;
        u2 name_index;
        u2 descriptor_index;
        u2 attributes_count;
        AttributeInfo *attributes;
    public:
        MethodInfo();
};


#endif