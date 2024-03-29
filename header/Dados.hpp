#include <stdint.h>
#include <vector>

#ifndef __Dados_HPP__
#define __Dados_HPP__

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;
typedef void *any;

#define CLASS 1
#define FIELD 2
#define METHOD 3
#define ATTRIBUTE 4

#define CONSTANT_Large 0
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

#endif