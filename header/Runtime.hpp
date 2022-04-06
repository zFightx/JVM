#ifndef __Runtime_HPP__
#define __Runtime_HPP__

#include <iostream>
#include <map>

#include "MethodAreaSection.hpp"
#include "Frame.hpp"

using namespace std;

class Runtime
{
private:
    
public:
    map<string, MethodAreaSection *> method_area;
    vector<Frame *> stack;
    int pc;

    Runtime(string class_name);
    ~Runtime();

    void AddStack(Frame *fr);
    void RemoveStack();

    void AddMethodArea(string class_name);
};

#endif