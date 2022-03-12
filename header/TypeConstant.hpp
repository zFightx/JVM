#ifndef __TypeConstant_HPP__
#define __TypeConstant_HPP__

#include <vector>
#include "Dados.hpp"

using namespace std;

struct CONSTANT_Class_info
{
    u2 name_index;
};

struct CONSTANT_Fieldref_info
{
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info
{
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info
{
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_NameAndType_info
{
    u2 name_index;
    u2 descriptor_index;
};

struct CONSTANT_Utf8_info
{
    u2 length;
    u1 *bytes;
};

struct CONSTANT_String_info
{
    u2 string_index;
};

struct CONSTANT_Integer_info
{
    u4 bytes;
};

struct CONSTANT_Float_info
{
    u4 bytes;
};

struct CONSTANT_Long_info
{
    u4 high_bytes; // unsigned
    u4 low_bytes;  // unsigned
};

struct CONSTANT_Double_info
{
    u4 high_bytes; // unsigned
    u4 low_bytes;  // unsigned
};

#endif