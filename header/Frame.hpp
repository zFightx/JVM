#ifndef __FRAME_H__
#define __FRAME_H__

#include<iostream>
#include<vector>

#include "CpInfo.hpp"
#include "TypeValue.hpp"

class Frame
{
private:
    
public:
    vector<Value> local_variables;
    vector<int> operand_stack;
    vector<CpInfo*> constant_pool;

    Frame();
    ~Frame();

    void AddLocalVariable(Value);
    void AddOperandStack(int);
    void SetContantPool(vector<CpInfo*> &cp);
};

#endif