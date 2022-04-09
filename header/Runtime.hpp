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
    static string main_class_name;
    map<string, MethodAreaSection *> method_area;
    vector<Frame *> stack;
    

    Runtime(string class_name);
    ~Runtime();

    void PushFrame(Frame *fr);
    void PopFrame();
    void InitializeFrame(string method_name, ClassFile *class_file);
    Frame * GetCurrentFrame();

    void AddMethodArea(string class_name);
};

#endif