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
    static vector<Value> args;

    map<string, MethodAreaSection *> method_area;
    vector<Frame *> stack;
    

    Runtime(string class_name, vector<Value> args = vector<Value> ());
    ~Runtime();

    void PushFrame(Frame *fr);
    void PopFrame();
    void InitializeFrame(string method_name, string descriptor, ClassFile *class_file, vector<Value> args = vector<Value>());
    Frame * GetCurrentFrame();

    void AddMethodArea(string class_name);
};

#endif