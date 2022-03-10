#include <string.h>
#include <iostream>

#include "../header/ClassFile.hpp"
#include "../header/ReadFile.hpp"
#include "../header/AttributeInfo.hpp"
#include "../header/ExceptionHandler.hpp"

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

ClassFile::ClassFile(string file)
{
    ifstream file_stream(file, ios::in | ios::binary);

    file_stream.seekg(0, ios::beg); // seek to the beginning of the file

    this->magic = ReadFile::u4Read(file_stream);
    this->minor_version = ReadFile::u2Read(file_stream);
    this->major_version = ReadFile::u2Read(file_stream);

    cout << "Iniciando Leitura de CPool" << endl;
    this->CreateConstantPool(file_stream);

    this->access_flags = ReadFile::u2Read(file_stream);
    this->this_class = ReadFile::u2Read(file_stream);
    this->super_class = ReadFile::u2Read(file_stream);

    this->CreateInterfaces(file_stream);

    this->CreateFieldInfo(file_stream);

    this->CreateMethodInfo(file_stream);

    this->attributes_count = ReadFile::u2Read(file_stream);
    this->attributes = this->CreateAttributeInfo(file_stream, this->attributes_count);

    //////////////////////////////////////////////////////////////////////////////////

    for (unsigned i = 0; i < this->constant_pool_count - 1; i++)
    {
        cout << "Tag " << dec << (int)this->constant_pool[i]->tag << endl;
    }

    cout << "finalizou com C_Count: " << dec << this->constant_pool_count - 1 << " e com armazenado: " << this->constant_pool.size() << endl;

    cout << "Qtd Interfaces: " << this->interfaces_count << endl;
    for (unsigned i = 0; i < this->interfaces_count; i++)
    {
        cout << "Interface " << dec << (int)this->interfaces[i] << endl;
    }

    cout << "Qtd Fields: " << this->fields_count << endl;
    for (unsigned i = 0; i < this->fields_count; i++)
    {

        u1 *bytes = this->constant_pool[this->fields[i]->name_index - 1]->info.Utf8.bytes;
        u2 length = this->constant_pool[this->fields[i]->name_index - 1]->info.Utf8.length;

        char array[length + 1];
        memcpy(array, bytes, length);

        array[length] = '\0';

        string name = array;

        cout << "Field Access F." << hex << (int)this->fields[i]->access_flags << endl;
        cout << "Field Name I." << dec << (int)this->fields[i]->name_index << " <" << name << ">" << endl;
        cout << "Field Desc I." << dec << (int)this->fields[i]->descriptor_index << endl;
        cout << "Field Attr C." << dec << (int)this->fields[i]->attributes_count << endl;

        for (unsigned j = 0; j < this->fields[i]->attributes_count; j++)
        {
            cout << "Field Attr Name I." << dec << (int)this->fields[i]->attributes[j]->attribute_name_index << endl;
            cout << "Field Attr Length." << dec << (int)this->fields[i]->attributes[j]->attribute_length << endl;
            cout << "Field Attr ConstantValue." << dec << (int)this->fields[i]->attributes[j]->info.ConstantValue.constantvalue_index << endl;
        }
    }

    cout << "--Methods--" << endl;
    cout << "Qtd Methods: " << this->methods_count << endl;
    for (unsigned i = 0; i < this->methods_count; i++)
    {
        cout << "Acc. flags: " << this->methods[i]->access_flags << endl;
        cout << "Name index: " << this->methods[i]->name_index << endl;
        cout << "Descr. index: " << this->methods[i]->descriptor_index << endl;
        cout << "Attr. Count: " << this->methods[i]->attributes_count << endl;

        for (unsigned j = 0; j < this->methods[i]->attributes_count; j++)
        {
            cout << "Attr. Name I: " << this->methods[i]->attributes[j]->attribute_name_index << endl;
            cout << "Attr. Length: " << this->methods[i]->attributes[j]->attribute_length << endl;
            cout << "Max Stack"
                 << ": " << this->methods[i]->attributes[j]->info.Code.max_stack << endl;
            cout << "Max Locals"
                 << ": " << this->methods[i]->attributes[j]->info.Code.max_locals << endl;
            cout << "Code Length"
                 << ": " << this->methods[i]->attributes[j]->info.Code.code_length << endl;
            for (unsigned k = 0; k < this->methods[i]->attributes[j]->info.Code.code_length; k++)
            {
                cout << "Code: " << hex << (int)this->methods[i]->attributes[j]->info.Code.code[k] << endl;
            }

            cout << "Exception Table Length"
                 << ": " << this->methods[i]->attributes[j]->info.Code.exception_table_length << endl;
            for (unsigned k = 0; k < this->methods[i]->attributes[j]->info.Code.exception_table_length; k++)
            {
                cout << "Exception Table"
                     << ": " << this->methods[i]->attributes[j]->info.Code.exception_table[k].start_pc << endl;
                cout << "Exception Table"
                     << ": " << this->methods[i]->attributes[j]->info.Code.exception_table[k].end_pc << endl;
                cout << "Exception Table"
                     << ": " << this->methods[i]->attributes[j]->info.Code.exception_table[k].handler_pc << endl;
                cout << "Exception Table"
                     << ": " << this->methods[i]->attributes[j]->info.Code.exception_table[k].catch_type << endl;
            }

            cout << "Attributes Count"
                 << ": " << this->methods[i]->attributes[j]->info.Code.attributes_count << endl;
            for (unsigned k = 0; k < this->methods[i]->attributes[j]->info.Code.attributes_count; k++)
            {
                cout << "Attr. name index"
                     << ": " << this->methods[i]->attributes[j]->info.Code.attributes[k].attribute_name_index << endl;
                cout << "Attr. length"
                     << ": " << this->methods[i]->attributes[j]->info.Code.attributes[k].attribute_length << endl;
            }
        }
    }

    cout << "Printando os Atributos Classe " << endl;

    for (unsigned i = 0; i < this->attributes_count; i++)
    {
        cout << dec << (int)this->attributes[i].attribute_name_index << endl;
    }
}

void ClassFile::CreateConstantPool(ifstream &file)
{
    this->constant_pool_count = ReadFile::u2Read(file);

    for (unsigned i = 0; i < this->constant_pool_count - 1; i++)
    {
        u1 tag = ReadFile::u1Read(file);
        CpInfo *cp = new CpInfo(tag);

        this->constant_pool.push_back(cp);

        switch (tag)
        {
        case CONSTANT_Class:
        {
            u2 name_index = ReadFile::u2Read(file);
            cp->info.Class.name_index = name_index;

            break;
        }
        case CONSTANT_Fieldref:
        {
            u2 class_index = ReadFile::u2Read(file);
            u2 name_and_type_index = ReadFile::u2Read(file);

            cp->info.Fieldref.class_index = class_index;
            cp->info.Fieldref.name_and_type_index = name_and_type_index;

            break;
        }
        case CONSTANT_Methodref:
        {
            u2 class_index = ReadFile::u2Read(file);
            u2 name_and_type_index = ReadFile::u2Read(file);

            cp->info.Methodref.class_index = class_index;
            cp->info.Methodref.name_and_type_index = name_and_type_index;

            break;
        }
        case CONSTANT_InterfaceMethodref:
        {
            u2 class_index = ReadFile::u2Read(file);
            u2 name_and_type_index = ReadFile::u2Read(file);

            cp->info.InterfaceMethodref.class_index = class_index;
            cp->info.InterfaceMethodref.name_and_type_index = name_and_type_index;

            break;
        }
        case CONSTANT_NameAndType:
        {
            u2 class_index = ReadFile::u2Read(file);
            u2 descriptor_index = ReadFile::u2Read(file);

            cp->info.NameAndType.class_index = class_index;
            cp->info.NameAndType.descriptor_index = descriptor_index;

            break;
        }
        case CONSTANT_Utf8:
        {
            u2 lenght = ReadFile::u2Read(file);
            u1 *bytes = new u1[lenght];

            for (unsigned j = 0; j < lenght; j++)
            {
                bytes[j] = ReadFile::u1Read(file);
            }

            cp->info.Utf8.length = lenght;
            cp->info.Utf8.bytes = bytes;

            break;
        }
        case CONSTANT_String:
        {
            u2 string_index = ReadFile::u2Read(file);

            cp->info.String.string_index = string_index;

            break;
        }
        case CONSTANT_Integer:
        {
            u4 bytes = ReadFile::u4Read(file);
            cp->info.Integer.bytes = bytes;

            break;
        }
        case CONSTANT_Float:
        {
            u4 bytes = ReadFile::u4Read(file);

            cp->info.Float.bytes = bytes;

            break;
        }
        case CONSTANT_Long:
        {
            u4 high_bytes = ReadFile::u4Read(file);
            u4 low_bytes = ReadFile::u4Read(file);

            cp->info.Long.high_bytes = high_bytes;
            cp->info.Long.low_bytes = low_bytes;

            break;
        }
        case CONSTANT_Double:
        {
            u4 high_bytes = ReadFile::u4Read(file);
            u4 low_bytes = ReadFile::u4Read(file);

            cp->info.Double.high_bytes = high_bytes;
            cp->info.Double.low_bytes = low_bytes;

            break;
        }
        }
    }
}
void ClassFile::CreateInterfaces(ifstream &file)
{
    this->interfaces_count = ReadFile::u2Read(file);
    for (unsigned i = 0; i < this->interfaces_count; i++)
    {
        u2 interface = ReadFile::u2Read(file);
        this->interfaces.push_back((int)interface);
    }
}

void ClassFile::CreateFieldInfo(ifstream &file)
{
    this->fields_count = ReadFile::u2Read(file);
    for (unsigned i = 0; i < this->fields_count; i++)
    {
        u2 access_flags = ReadFile::u2Read(file);
        u2 name_index = ReadFile::u2Read(file);
        u2 descriptor_index = ReadFile::u2Read(file);
        u2 attributes_count = ReadFile::u2Read(file);

        FieldInfo *field = new FieldInfo(access_flags, name_index, descriptor_index, attributes_count);

        // for (unsigned j = 0; j < attributes_count; j++)
        // {
        //     u2 attribute_name_index = ReadFile::u2Read(file);
        //     u4 attribute_length = ReadFile::u4Read(file);
        //     AttributeInfo *attribute = new AttributeInfo(attribute_name_index, attribute_length);
        //     attribute->info.ConstantValue.constantvalue_index = ReadFile::u2Read(file);
        //     field->attributes.push_back(attribute);
        // }

        AttributeInfo *attributes = this->CreateAttributeInfo(file, attributes_count);
        field->attributes.push_back(attributes);

        this->fields.push_back(field);
    }
}

void ClassFile::CreateMethodInfo(ifstream &file)
{
    this->methods_count = ReadFile::u2Read(file);
    for (unsigned i = 0; i < this->methods_count; i++)
    {

        u2 access_flags = ReadFile::u2Read(file);
        u2 name_index = ReadFile::u2Read(file);
        u2 descriptor_index = ReadFile::u2Read(file);
        u2 attributes_count = ReadFile::u2Read(file);

        MethodInfo *method = new MethodInfo(access_flags, name_index, descriptor_index, attributes_count);

        // cout << "Entrando attribute" << endl;
        AttributeInfo *attribute = CreateAttributeInfo(file, attributes_count);
        method->attributes.push_back(attribute);

        this->methods.push_back(method);
    }
}

AttributeInfo *ClassFile::CreateAttributeInfo(ifstream &file, u2 attributes_count)
{
    // cout << "Chamada de CreateAttributeInfo" << endl;
    AttributeInfo *attributes = new AttributeInfo[attributes_count];

    for (unsigned i = 0; i < attributes_count; i++)
    {
        u2 attribute_name_index = ReadFile::u2Read(file);
        u4 attribute_length = ReadFile::u4Read(file);

        attributes[i] = AttributeInfo(attribute_name_index, attribute_length);

        u1 *bytes = this->constant_pool[attribute_name_index - 1]->info.Utf8.bytes;
        u2 length = this->constant_pool[attribute_name_index - 1]->info.Utf8.length;

        char array[length + 1];
        memcpy(array, bytes, length);

        array[length] = '\0';

        string name = array;

        cout << name << endl;

        // cout << name << endl;
        if (name == "SourceFile")
        {
            u2 sourcefile_index = ReadFile::u2Read(file);
            attributes[i].info.SourceFile.sourcefile_index = sourcefile_index;
        }
        else if (name == "ConstantValue")
        {
            attributes[i].info.ConstantValue.constantvalue_index = ReadFile::u2Read(file);
        }
        else if (name == "InnerClasses")
        {
            u2 number_of_classes = ReadFile::u2Read(file);
            attributes[i].info.InnerClasses.number_of_classes = number_of_classes;

            attributes[i].info.InnerClasses.classes = new Classes[number_of_classes];

            for (unsigned j = 0; j < number_of_classes; j++)
            {
                u2 inner_class_info_index = ReadFile::u2Read(file);
                u2 outer_class_info_index = ReadFile::u2Read(file);
                u2 inner_name_index = ReadFile::u2Read(file);
                u2 inner_class_access_flags = ReadFile::u2Read(file);

                attributes[i].info.InnerClasses.classes[j] = Classes(inner_class_info_index, outer_class_info_index, inner_name_index, inner_class_access_flags);
            }
        }
        else if (name == "Code")
        {
            attributes[i].info.Code.max_stack = ReadFile::u2Read(file);
            attributes[i].info.Code.max_locals = ReadFile::u2Read(file);
            attributes[i].info.Code.code_length = ReadFile::u4Read(file);

            u1 *code = new u1[attributes[i].info.Code.code_length];
            for (unsigned k = 0; k < attributes[i].info.Code.code_length; k++)
            {
                u1 opcode = ReadFile::u1Read(file);
                code[k] = opcode;
            }

            attributes[i].info.Code.code = code;

            attributes[i].info.Code.exception_table_length = ReadFile::u2Read(file);

            ExceptionHandler *ExceptionTable = new ExceptionHandler[attributes[i].info.Code.exception_table_length];
            for (unsigned k = 0; k < attributes[i].info.Code.exception_table_length; k++)
            {
                u2 start_pc = ReadFile::u2Read(file);
                u2 end_pc = ReadFile::u2Read(file);
                u2 handler_pc = ReadFile::u2Read(file);
                u2 catch_type = ReadFile::u2Read(file);

                ExceptionHandler handler = ExceptionHandler(start_pc, end_pc, handler_pc, catch_type);
                ExceptionTable[k] = handler;
            }
            attributes[i].info.Code.exception_table = ExceptionTable;

            attributes[i].info.Code.attributes_count = ReadFile::u2Read(file);
            // cout << "Entrando Atribute via Code" << endl;
            attributes[i].info.Code.attributes = CreateAttributeInfo(file, attributes[i].info.Code.attributes_count);
        }
        else if (name == "Exceptions")
        {
            u2 number_of_exceptions = ReadFile::u2Read(file);
            attributes[i].info.Exceptions.number_of_exceptions = number_of_exceptions;
            attributes[i].info.Exceptions.exception_index_table = new u2[number_of_exceptions];
            for (unsigned j = 0; j < number_of_exceptions; j++)
            {
                attributes[i].info.Exceptions.exception_index_table[j] = ReadFile::u2Read(file);
            }
        }
        else
        {
            for (unsigned j = 0; j < attributes[i].attribute_length; j++)
            {
                ReadFile::u1Read(file);
            }
        }
        // attributes.push_back(attribute);
    }
    return attributes;
}
