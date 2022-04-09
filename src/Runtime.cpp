#include "../header/Runtime.hpp"
#include "../header/ClassLoaderSubsystem.hpp"

string Runtime::main_class_name;

Runtime::Runtime(string class_name)
{
    Runtime::main_class_name = class_name;
    // this->AddMethodArea(class_name);

    // this->func = &Runtime::Print;
    // (this->*func)();
}

Runtime::~Runtime()
{
}

void Runtime::PushFrame(Frame* frame)
{
    this->stack.push_back(frame);
}

void Runtime::PopFrame()
{
    this->stack.pop_back();
}

void Runtime::InitializeFrame(string method_name, ClassFile* class_file){
    MethodInfo* method = class_file->getMethodByName(method_name);

    if(method)
    {
        AttributeInfo attr; 
        method->getAttributeByName("Code", class_file->constant_pool, attr);
        Code_attribute code = attr.info.Code;
        
        Frame *fr = new Frame(class_file->constant_pool, code);
        this->PushFrame(fr);
    }
}

Frame * Runtime::GetCurrentFrame(){
    return this->stack[0];
}


void Runtime::AddMethodArea(string class_name)
{
    // ClassLoaderSubsystem::Resolve(class_name, this->method_area);
}