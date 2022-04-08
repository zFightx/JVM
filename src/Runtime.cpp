#include "../header/Runtime.hpp"
#include "../header/ClassLoaderSubsystem.hpp"

Runtime::Runtime(string class_name)
{
    Runtime::main_class_name = class_name;
    this->AddMethodArea(class_name);
}

Runtime::~Runtime()
{
}

void Runtime::AddMethodArea(string class_name)
{
    ClassLoaderSubsystem::Resolve(class_name, this->method_area);
}