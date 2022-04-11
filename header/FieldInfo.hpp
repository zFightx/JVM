#ifndef __FieldInfo_HPP__
#define __FieldInfo_HPP__

#include <vector>
#include "Dados.hpp"
#include "AttributeInfo.hpp"
#include "TypeValue.hpp"

using namespace std;

struct Value;

class FieldInfo
{
public:
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo * attributes;
    FieldInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count);
    ~FieldInfo();

    Value FieldInit(string field_descriptor);
};

#endif