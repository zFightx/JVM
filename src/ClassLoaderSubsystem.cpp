#include <iostream>

#include "../header/ClassLoaderSubsystem.hpp"
#include "../header/Dados.hpp"
#include "../header/ClassFile.hpp"
#include "../header/ReadFile.hpp"
#include "../header/Runtime.hpp"
#include "../header/FieldInfo.hpp"

using namespace std;

void ClassLoaderSubsystem::Verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName)

{
    if (cafeBabe != 0xCAFEBABE)
    {
        throw "Invalid magic number!";
        // cout << "Invalid magic number" << endl;
        exit(1);
    }
    if (minorVersion != 0)
    {
        throw "Invalid minor version!";
        // cout << "Invalid minor version" << endl;
        exit(1);
    }
    if (majorVersion < 45 || majorVersion > 52)
    {
        throw "Invalid major version!";
        // cout << "Invalid major version" << endl;
        exit(1);
    }

    if (sourceFileFontName != fontName)
    {
        throw "Invalid source file name!";
        // cout << "Invalid source file name" << endl;
        exit(1);
    }
}

void ClassLoaderSubsystem::Prepare(ClassFile *cf)
{
    // vector<CpInfo *> cp = cf->constant_pool;
    // vector<MethodInfo *> methods = cf->methods;
    // map <string, value>
}

void ClassLoaderSubsystem::Resolve(string class_name, Runtime *runtime)
{
    map<string, MethodAreaSection *> &method_area = runtime->method_area;

    // se classe ainda não carregada
    if (!method_area.count(class_name))
    {
        class_name = class_name.find(".class") != string::npos ? class_name : class_name + ".class";

        ClassFile *class_file = new ClassFile(class_name);
        MethodAreaSection *new_method_area = new MethodAreaSection(class_file);

        u2 index = class_file->constant_pool[class_file->this_class - 1]->info.Class.name_index;
        string this_class = ReadFile::readString(index, class_file->constant_pool);

        vector<FieldInfo *> fields = class_file->fields;
        for (unsigned i = 0; i < class_file->fields_count; i++)
        {
            if (fields[i]->access_flags == 0x0008)
            {
                string field_name = ReadFile::readString(fields[i]->name_index, class_file->constant_pool);
                string field_descriptor = ReadFile::readString(fields[i]->descriptor_index, class_file->constant_pool);

                Value value = FieldInfo::FieldInit(field_descriptor);
                new_method_area->static_fields.insert({field_name, value});
            }
        }

        method_area.insert({this_class, new_method_area});
        
        // chamar Initialize da classe
        ClassLoaderSubsystem::Initialize(class_file, runtime);
        if (class_file->super_class != 0)
        {
            u2 index = class_file->constant_pool[class_file->super_class - 1]->info.Class.name_index;
            string super_class = ReadFile::readString(index, class_file->constant_pool);
            ClassLoaderSubsystem::Resolve(super_class, runtime);
        }
    }
}

// se for a main class, empilhar o metodo main primeiro e depois o clinit, caso contrário, só empilhar o clinit
void ClassLoaderSubsystem::Initialize(ClassFile *class_file, Runtime *runtime)
{  
    string class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool) + ".class";
    if (class_name == Runtime::main_class_name)
    {   
        runtime->InitializeFrame("main", "([Ljava/lang/String;)V", class_file, Runtime::args);
    }

    runtime->InitializeFrame("<clinit>", "()V", class_file);
}

// string ClassLoaderSubsystem::GetStringConstantPool(u2 index, vector<CpInfo *> constant_pool)
// {
//     CpInfo *cp = constant_pool[index - 1];

//     u1 *bytes = cp->info.Utf8.bytes;
//     u2 length = cp->info.Utf8.length;
//     string name = ReadFile::readByteString(bytes, length);

//     return name;
// }