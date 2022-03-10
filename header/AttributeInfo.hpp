#ifndef __AttributeInfo_HPP__
#define __AttributeInfo_HPP__

#include <vector>

#include "Dados.hpp"
#include "TypeAttribute.hpp"

class AttributeInfo
{
public:
    u2 attribute_name_index;
    u4 attribute_length;
    union Info
    {
        ConstantValue_attribute ConstantValue;
        Code_attribute Code;
        Exceptions_attribute Exceptions;
        InnerClasses_attribute InnerClasses;
        Synthetic_attribute Synthetic;
        SourceFile_attribute SourceFile;
        
    } info;
    AttributeInfo();
    AttributeInfo(u2 attribute_name_index, u4 attribute_length);
};

#endif