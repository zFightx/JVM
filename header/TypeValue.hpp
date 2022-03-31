#ifndef __TypeValue_hpp__
#define __TypeValue_hpp__

#include <iostream>
#include "Dados.hpp"

using namespace std;

typedef struct Value
{
    char type;
    union
    {
        int8_t byteValue;   // B
        uint16_t charValue; // C
        double doubleValue; // D
        float floatValue;   // F
        int32_t intValue;   // I
        int64_t longValue;  // J
        any objectValue;    // L
        int16_t shortValue; // S
        bool booleanValue;  // Z
        any arrayValue;     // [
    } data;
} value;

#endif