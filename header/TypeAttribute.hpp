#ifndef __TypeAttribute_HPP__
#define __TypeAttribute_HPP__

#include <vector>

#include "Dados.hpp"
#include "AttributeInfo.hpp"
#include "ExceptionHandler.hpp"
#include "Classes.hpp"

using namespace std;

// utilizado em FieldInfo
struct ConstantValue_attribute
{
    u2 constantvalue_index; // indice de uma estrutura CONSTANT(long, float, double, integer ou string)
};

// utilizado em MethodInfo
// metodo nativo ou abstrato nao possui esse atributo
struct Code_attribute
{
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    vector<u1> code;
    u2 exception_table_length;
    vector<ExceptionHandler *> *exception_table;
    u2 attributes_count;
    vector<AttributeInfo *> attributes;
};

struct Exceptions_attribute
{
    u2 number_of_exceptions;          // numero de entradas na exception_index_table
    vector<u2> exception_index_table; // indice pra constant pool de CONSTANT_Class_info
};

struct InnerClasses_attribute
{
    u2 number_of_classes;
    vector<Classes *> classes;
};

struct Synthetic_attribute
{
};

#endif