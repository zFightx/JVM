#ifndef __ClassFile_HPP__
#define __ClassFile_HPP__

#include <iostream>
#include <vector>

#include "Dados.hpp"
#include "CpInfo.hpp"
#include "FieldInfo.hpp"
#include "MethodInfo.hpp"
#include "AttributeInfo.hpp"

using namespace std;

class ClassFile{
    private:
        u4 magic;
        u2 minor_version;
        u2 major_version;
        u2 constant_pool_count;
        vector<CpInfo*> constant_pool;
        u2 access_flags;
        u2 this_class;
        u2 super_class;
        u2 interfaces_count;
        u2 *interfaces;
        u2 fields_count;
        FieldInfo *fields;
        u2 methods_count;
        MethodInfo *methods;
        u2 attributes_count;
        AttributeInfo *attributes; 

    public:
        ClassFile(string file);
};

#endif