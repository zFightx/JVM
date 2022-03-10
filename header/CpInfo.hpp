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
            CONSTANT_Class_info Class;
            CONSTANT_Fieldref_info Fieldref;
            CONSTANT_Methodref_info Methodref;
            CONSTANT_InterfaceMethodref_info InterfaceMethodref;
            CONSTANT_NameAndType_info NameAndType;
            CONSTANT_Utf8_info Utf8;
            CONSTANT_String_info String;
            CONSTANT_Integer_info Integer;
            CONSTANT_Float_info Float;
            CONSTANT_Long_info Long;
            CONSTANT_Double_info Double;
        } info;
        
        CpInfo(u1 tag);
        ~CpInfo();
};


#endif