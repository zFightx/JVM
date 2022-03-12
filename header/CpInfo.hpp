#ifndef __CpInfo_HPP__
#define __CpInfo_HPP__

#include "Dados.hpp"
#include "TypeConstant.hpp"

class CpInfo
{
public:
    u1 tag;
    union info
    {
        CONSTANT_Class_info Class;                           // 7
        CONSTANT_Fieldref_info Fieldref;                     // 9
        CONSTANT_Methodref_info Methodref;                   // 10
        CONSTANT_InterfaceMethodref_info InterfaceMethodref; // 11
        CONSTANT_NameAndType_info NameAndType;               // 12
        CONSTANT_Utf8_info Utf8;                             // 1
        CONSTANT_String_info String;                         // 8
        CONSTANT_Integer_info Integer;                       // 3
        CONSTANT_Float_info Float;                           // 4
        CONSTANT_Long_info Long;                             // 5
        CONSTANT_Double_info Double;                         // 6
    } info;

    CpInfo(u1 tag);
    ~CpInfo();
};

#endif