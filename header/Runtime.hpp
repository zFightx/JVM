#ifndef __Runtime_HPP__
#define __Runtime_HPP__

#include <iostream>
#include <map>

#include "MethodAreaSection.hpp"

using namespace std;

class Runtime
{
private:
    
public:
    map<string, MethodAreaSection *> method_area;

    Runtime(string class_name);
    ~Runtime();
};

#endif