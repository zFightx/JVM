#ifndef __MethodAreaSection_hpp__
#define __MethodAreaSection_hpp__

#include <iostream>
#include <map>

#include "ClassFile.hpp"
#include "TypeValue.hpp"

class MethodAreaSection
{
public:
    vector<CpInfo *> constant_pool;
    vector<MethodInfo *> methods;
    map<string, value> variables;

    MethodAreaSection(ClassFile *cf);
};

#endif
