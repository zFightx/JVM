#ifndef __MethodAreaSection_hpp__
#define __MethodAreaSection_hpp__

#include <iostream>
#include <map>

#include "ClassFile.hpp"
#include "TypeValue.hpp"

class MethodAreaSection
{
public:
    ClassFile * class_file;
    map<string, Value> static_fields;

    MethodAreaSection(ClassFile *cf);
};

#endif
