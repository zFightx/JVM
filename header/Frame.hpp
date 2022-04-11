#ifndef __FRAME_H__
#define __FRAME_H__

#include <iostream>
#include <vector>
#include <map>

#include "CpInfo.hpp"
#include "TypeValue.hpp"

class Frame
{
private:
    
public:
    map<int, Value> local_variables;
    vector<Value> operand_stack;
    vector<CpInfo*> constant_pool;
    Code_attribute code;
    int pc;

    Frame();
    Frame(vector<CpInfo*> constant_pool, Code_attribute code);
    ~Frame();

    void PushOperandStack(Value);
    Value PopOperandStack();

    void AddLocalVariable(Value);
    Value GetLocalVariable(int index);
    void ChangeLocalVariable(int index, Value);
    void AddOperandStack(Value);
    void SetContantPool(vector<CpInfo*> &cp);
};

#endif