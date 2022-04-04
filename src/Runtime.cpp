#include "../header/Runtime.hpp"
#include "../header/ClassLoaderSubsystem.hpp"

Runtime::Runtime(string class_name){
    ClassLoaderSubsystem::Resolve(class_name, this->method_area);
}

Runtime::~Runtime(){

}
