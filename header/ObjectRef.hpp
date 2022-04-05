#ifndef __OBJECTREF_HPP__
#define __OBJECTREF_HPP__

#include "TypeValue.hpp"

#include <string>
#include <map>

using namespace std;

class ObjectRef
{
public:
    map <string, Value> variables;

    ObjectRef(/* args */);
    ~ObjectRef();
};

#endif