#ifndef __TypeValue_hpp__
#define __TypeValue_hpp__

#include <iostream>

#include "Dados.hpp"
#include "ObjectRef.hpp"

using namespace std;

struct Value
{
    char type;
    union
    {
        int8_t byte_value;   // B
        uint16_t char_value; // C
        double double_value; // D
        float float_value;   // F
        int32_t int_value;   // I
        int64_t long_value;  // J
        ObjectRef *object_value;    // L
        int16_t short_value; // S
        bool boolean_value;  // Z
        any array_value;     // [
    } data;
};

#endif