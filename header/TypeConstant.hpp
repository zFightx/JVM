#ifndef __TypeConstant_HPP__
#define __TypeConstant_HPP__

#include "Dados.hpp"

struct CONSTANT_Class_info{
    u1 tag; // 7
    u2 name_index;
};

struct CONSTANT_Fieldref_info{
    u1 tag; // 9
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info{
    u1 tag; // 10
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info{
    u1 tag; // 11
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_NameAndType_info{
    u1 tag; // 12
    u2 class_index;
    u2 descriptor_index;
};

struct CONSTANT_Utf8_info{
    u1 tag; // 1
    u2 length;
    u2 *bytes;
};

struct CONSTANT_String_info{
    u1 tag; // 8
    u2 string_index;
};

struct CONSTANT_Integer_info{
    u1 tag; // 3
    u4 bytes;
};

struct CONSTANT_Float_info{
    u1 tag; // 4
    u4 bytes;
};

struct CONSTANT_Long_info{
    u1 tag; // 5
    u4 high_bytes; // unsigned
    u4 low_bytes; // unsigned
};

struct CONSTANT_Double_info{
    u1 tag; // 6
    u4 high_bytes; // unsigned
    u4 low_bytes; // unsigned
};

#endif