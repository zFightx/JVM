#ifndef __OBJECTREF_HPP__
#define __OBJECTREF_HPP__

#include "ClassFile.hpp"
#include "TypeValue.hpp"

#include <string>
#include <map>

using namespace std;

class ObjectRef
{
public:
    map <string, Value> variables;

    ObjectRef(ClassFile *class_file);
    ~ObjectRef();

    void AddVariable(string, Value);
    void ChangeVariable(string, Value);
    Value GetVariable(string);
};

#endif