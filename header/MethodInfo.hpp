#ifndef __MethodInfo_HPP__
#define __MethodInfo_HPP__

#include <vector>
#include <iostream>

#include "Dados.hpp"
#include "AttributeInfo.hpp"
#include "CpInfo.hpp"

using namespace std;

class MethodInfo
{
private:
public:
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo *attributes;
    MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count);
    ~MethodInfo();

    void getAttributeByName(string name, vector<CpInfo*> constant_pool, AttributeInfo &copy);
    
};
#endif