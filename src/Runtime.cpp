#include "../header/Runtime.hpp"
#include "../header/ClassLoaderSubsystem.hpp"
#include "../header/ReadFile.hpp"

string Runtime::main_class_name;
vector<Value> Runtime::args;

Runtime::Runtime(string class_name, vector<Value> args)
{
    Runtime::main_class_name = class_name;
    Runtime::args = args;
}

Runtime::~Runtime()
{
    for( unsigned i = 0; i < this->stack.size(); i++){
        delete this->stack[i];
    }
    
    map<string, MethodAreaSection*>::iterator it;

    for (it = this->method_area.begin(); it != this->method_area.end(); it++){
        delete it->second;
    }

}

void Runtime::PushFrame(Frame* frame)
{
    this->stack.push_back(frame);
}

void Runtime::PopFrame()
{
    Frame * to_delete = this->GetCurrentFrame();
    delete to_delete;
    this->stack.pop_back();
}

// Checa se a classe passada ja foi resolvida, se nao, resolve e entao busca um metodo de acordo com o nome e o descritor no class file
void Runtime::InitializeFrame(string method_name, string descriptor, ClassFile* class_file, vector<Value> args){
    // verificar se o method area existe para o class_name e se não existir criar

    string class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool);
    if (this->method_area.count(class_name) == 0){
        ClassLoaderSubsystem::Resolve(class_name, this);
    }

    MethodInfo* method = class_file->getMethodByNameAndDescriptor(method_name, descriptor);

    if(method)
    {
        AttributeInfo attr; 
        method->getAttributeByName("Code", class_file->constant_pool, attr);
        Code_attribute code = attr.info.Code;

        Frame *fr = new Frame(class_file->constant_pool, code);
      
        this->PushFrame(fr);

        for(unsigned i = 0 ; i < args.size(); i++){
            fr->ChangeLocalVariable(i, args[i]);
        }
    }
}

Frame * Runtime::GetCurrentFrame(){
    return this->stack[this->stack.size()-1];
}


void Runtime::AddMethodArea(string class_name)
{
    // ClassLoaderSubsystem::Resolve(class_name, this->method_area);
}