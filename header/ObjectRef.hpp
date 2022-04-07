#ifndef __ObjectRef_HPP__
#define __ObjectRef_HPP__

#include <string>
#include <map>

#include "TypeValue.hpp"
#include "ClassFile.hpp"

using namespace std;

struct Value;

class ObjectRef
{
public:
    map<string, Value> variables;

    ObjectRef(ClassFile *class_file);
    ~ObjectRef();

    void AddVariable(string, Value);
    void ChangeVariable(string, Value);
    Value GetVariable(string);
};

#endif