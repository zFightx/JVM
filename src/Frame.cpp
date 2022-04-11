#include "../header/Frame.hpp"

Frame::Frame(){
    this->pc = 0;
}

Frame::Frame(vector<CpInfo*> constant_pool, Code_attribute code){
    this->constant_pool = constant_pool;
    this->code = code;
    this->pc = 0;    
}
Frame::~Frame(){

}

void Frame::PushOperandStack(Value value){
    this->operand_stack.push_back(value);
}

Value Frame::PopOperandStack(){
    Value value = this->operand_stack.back();
    this->operand_stack.pop_back();
    return value;
}

Value Frame::GetLocalVariable(int index){
    return this->local_variables[index];
}

void Frame::ChangeLocalVariable(int index, Value value){
    // if(this->local_variables.size() > index)
        this->local_variables[index] = value;
    // else
    //     this->local_variables.push_back(value);
}

void Frame::AddLocalVariable(Value value){
    // this->local_variables.push_back(value);
}

void Frame::AddOperandStack(Value value){
    this->operand_stack.push_back(value);
}

void Frame::SetContantPool(vector<CpInfo*> &cp){
    this->constant_pool = cp;
}
