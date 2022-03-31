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

class ClassFile
{

public:
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    vector<CpInfo *> constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    vector<u2> interfaces;
    u2 fields_count;
    vector<FieldInfo *> fields;
    u2 methods_count;
    vector<MethodInfo *> methods;
    u2 attributes_count;
    AttributeInfo *attributes;

    ClassFile(string file);
    ~ClassFile();
    void CreateConstantPool(ifstream &file);
    void CreateInterfaces(ifstream &file);
    void CreateFieldInfo(ifstream &file);
    void CreateMethodInfo(ifstream &file);

    AttributeInfo *CreateAttributeInfo(ifstream &file, u2 attributes_count);
    void DeleteAttributes(AttributeInfo *attributes, u2 attributes_count);

    void MenuClassFile();
    void GeneralInformation();
    void MenuConstantPool();
    void MenuInterfaces();
    void MenuFields();
    void MenuAttributes();
    void MenuMethodInfo();
    void PrintAttributes(AttributeInfo *attributes, u2 attributes_count);
    void PrintAccessFlags(u2 access_flags, int flagType);

    string readString(int index);
};

#endif