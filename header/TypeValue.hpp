#ifndef __TypeValue_HPP__
#define __TypeValue_HPP__

#include <iostream>

#include "ObjectRef.hpp"
#include "Dados.hpp"

using namespace std;

#define BYTE_VALUE 0 // B  0
#define CHAR_VALUE 1 // C  1
#define DOUBLE_VALUE 2 // D  2
#define FLOAT_VALUE 3 // F  3
#define INT_VALUE 4 // I  4
#define LONG_VALUE 5 // J  5
#define SHORT_VALUE 6 // S  6
#define BOOLEAN_VALUE 7 // Z  7
#define OBJECT_VALUE 8 // L  8

class ObjectRef;

struct Value
{
    char type;
    union
    {
        int8_t byte_value;       // B  0
        uint16_t char_value;     // C  1
        double double_value;     // D  2
        float float_value;       // F  3
        int32_t int_value;       // I  4
        int64_t long_value;      // J  5
        int16_t short_value;     // S  6
        bool boolean_value;      // Z  7
        ObjectRef *object_value; // L  8
        // any array_value;         // [  3
    } data;
};

typedef struct Value Value;

#endif