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
    file_stream.seekg(0, ios::beg);

    this->magic = ReadFile::u4Read(file_stream);
    this->minor_version = ReadFile::u2Read(file_stream);
    this->major_version = ReadFile::u2Read(file_stream);

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
}

void ClassFile::MenuClassFile(){
    int opcao = -1;

    while (opcao != 0){
        cout << "Bytecode Viewer SB" << endl;
        cout << "Escolha o que deseja fazer: " << endl << endl;
        cout << "[1] General Information" << endl;
        cout << "[2] Constant Pool" << endl;
        cout << "[3] Interfaces" << endl;
        cout << "[4] Fields" << endl;
        cout << "[5] Methods" << endl;
        cout << "[6] Attributes" << endl;
        cout << "[0] Encerrar" << endl;
        cout << endl << "Digite uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
            case 0:{
                break;
            }
            case 1:{
                this->GeneralInformation();
                break;
            }
            case 2:{
                this->MenuConstantPool();                
                break;
            }
            case 3:{
                this->MenuInterfaces();
                break;
            }
            case 4:{
                this->MenuFields();
                break;
            }
            case 5:{
                
                break;
            }
            case 6:{
                this->MenuAttributes();
                break;
            }
        }
    }
}

void ClassFile::GeneralInformation(){
    CpInfo *cp = this->constant_pool[this->this_class-1];
    CpInfo *this_class = this->constant_pool[cp->info.Class.name_index-1];

    cp = this->constant_pool[this->super_class-1];
    CpInfo *super_class = this->constant_pool[cp->info.Class.name_index-1];

    float major_version = 1.1;

    switch (this->major_version)
    {
        case 45: {
            major_version = 1.1;
            break;
        }
        case 46: {
            major_version = 1.2;
            break;
        }
        case 47: {
            major_version = 1.3;
            break;
        }
        case 48: {
            major_version = 1.4;
            break;
        }
        case 49: {
            major_version = 1.5;
            break;
        }
        case 50: {
            major_version = 1.6;
            break;
        }
        case 51: {
            major_version = 1.7;
            break;
        }
        case 52: {
            major_version = 1.8;
            break;
        }
        case 53: {
            major_version = 9;
            break;
        }
        case 54: {
            major_version = 10;
            break;
        }
        case 55: {
            major_version = 11;
            break;
        }
        case 56: {
            major_version = 12;
            break;
        }
        case 57: {
            major_version = 13;
            break;
        }
        case 58: {
            major_version = 14;
            break;
        }
        case 59: {
            major_version = 15;
            break;
        }
        case 60: {
            major_version = 16;
            break;
        }
    }

    cout << "Minor version: " << this->minor_version << endl;
    cout << "Major version: " << dec << (int) this->major_version << " [" << major_version << "]" << endl;
    cout << "Constant pool count: " << this->constant_pool_count << endl;
    cout << "Access flags: " << hex << this->access_flags << endl;
    cout << "This class: cp_info #" << this->this_class << " <" << this_class->info.Utf8.bytes << ">" << endl;
    cout << "Super class: cp_info #" << this->super_class << " <" << super_class->info.Utf8.bytes << ">" << endl;
    cout << "Interfaces count: " << this->interfaces_count << endl;
    cout << "Fields count: " << this->fields_count << endl;
    cout << "Methods count: " << this->methods_count << endl;
    cout << "Attributes count: " << this->attributes_count << endl;
}

void ClassFile::MenuConstantPool(){
    int opcao = -1;

    cout << "Constant Pool" << endl;

    for(unsigned i = 0; i < this->constant_pool_count -1; i++){
        CpInfo *cp = this->constant_pool[i];
        switch (cp->tag)
        {
            case CONSTANT_Class: {
                cout << "[" << dec << i+1 << "]" << " CONSTANT_Class_info" << endl;
                break;
            }
            case CONSTANT_Fieldref: {
                cout << "[" << i+1 << "]" << " CONSTANT_Fieldref_info" << endl;
                break;
            }
            case CONSTANT_Methodref: {
                cout << "[" << i+1 << "]" << " CONSTANT_Methodref_info" << endl;
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                cout << "[" << i+1 << "]" << " CONSTANT_InterfaceMethodref_info" << endl;
                break;
            }
            case CONSTANT_String: {
                cout << "[" << i+1 << "]" << " CONSTANT_String_info" << endl;
                break;
            }
            case CONSTANT_Integer: {
                cout << "[" << i+1 << "]" << " CONSTANT_Integer_info" << endl;
                break;
            }
            case CONSTANT_Float: {
                cout << "[" << i+1 << "]" << " CONSTANT_Float_info" << endl;
                break;
            }
            case CONSTANT_Long: {
                cout << "[" << i+1 << "]" << " CONSTANT_Long_info" << endl;
                break;
            }
            case CONSTANT_Double: {
                cout << "[" << i+1 << "]" << " CONSTANT_Double_info" << endl;
                break;
            }
            case CONSTANT_NameAndType: {
                cout << "[" << i+1 << "]" << " CONSTANT_NameAndType_info" << endl;
                break;
            }
            case CONSTANT_Utf8: {
                cout << "[" << i+1 << "]" << " CONSTANT_Utf8_info" << endl;
                break;
            }
        }
        
    }

    while (opcao != 0){
        cout << endl << "Digite uma opcao: ";
        cin >> opcao;

        if(opcao-1 >= 0 && opcao-1 < this->constant_pool_count-1){
            CpInfo * cp = this->constant_pool[opcao-1];

            switch (cp->tag)
            {
                case CONSTANT_Class: {
                    u1 *bytes = this->constant_pool[cp->info.Class.name_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.Class.name_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);

                    cout << endl << "Class name: cp_info #" << cp->info.Class.name_index << " <" << bytes << ">" << endl;
                    break;
                }
                case CONSTANT_Fieldref: {
                    u1 *bytes = this->constant_pool[cp->info.Fieldref.class_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.Fieldref.class_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "Class name: cp_info #" << cp->info.Fieldref.class_index << " <" << ">" << endl;
                    cout << "Name and type: cp_info #" << cp->info.Fieldref.name_and_type_index << " <" << ">" << endl;
                    break;
                }
                case CONSTANT_Methodref: {
                    u1 *bytes = this->constant_pool[cp->info.Methodref.class_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.Methodref.class_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "Class name: cp_info #" << cp->info.Methodref.class_index << " <" << ">" << endl;
                    cout << "Name and type: cp_info #" << cp->info.Methodref.name_and_type_index << " <" << ">" << endl;

                    break;
                }
                case CONSTANT_InterfaceMethodref: {
                    u1 *bytes = this->constant_pool[cp->info.InterfaceMethodref.class_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.InterfaceMethodref.class_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "Class name: cp_info #" << cp->info.InterfaceMethodref.class_index << " <" << ">" << endl;
                    cout << "Name and type: cp_info #" << cp->info.InterfaceMethodref.name_and_type_index << " <" << ">" << endl;
                    break;
                }
                case CONSTANT_String: {
                    u1 *bytes = this->constant_pool[cp->info.String.string_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.String.string_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "String: cp_info #" << cp->info.String.string_index << " <" << ">" << endl;
                    break;
                }
                case CONSTANT_Integer: {
                    cout << endl << "Bytes: " << hex << (int) cp->info.Integer.bytes << endl;
                    cout << "Integer: " << dec << (int) cp->info.Integer.bytes << endl;
                    break;
                }
                case CONSTANT_Float: {
                    cout << endl << "Bytes: " << hex << (int) cp->info.Float.bytes << endl;
                    cout << "Integer: " << dec << (int) cp->info.Float.bytes << endl;
                    break;
                }
                case CONSTANT_Long: {
                    // cout << endl << "Bytes: " << hex << (int) cp->info.Float.bytes << endl;
                    // cout << endl << "Integer: " << dec << (int) cp->info.Float.bytes << endl;
                    break;
                }
                case CONSTANT_Double: {
                    
                    break;
                }
                case CONSTANT_NameAndType: {
                    u1 *bytes = this->constant_pool[cp->info.NameAndType.name_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.NameAndType.name_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "Name: cp_info #" << cp->info.NameAndType.name_index << " <" << ">" << endl;
                    cout << "Descriptor: cp_info #" << cp->info.NameAndType.descriptor_index << " <" << ">" << endl;
                    break;
                }
                case CONSTANT_Utf8: {
                    u1 *bytes = this->constant_pool[cp->info.NameAndType.name_index-1]->info.Utf8.bytes;
                    u2 length = this->constant_pool[cp->info.NameAndType.name_index-1]->info.Utf8.length;
                    // ReadFile::readByteString(bytes, length);
                    // arrumar o cout

                    cout << endl << "Length of byte array: " << cp->info.Utf8.length << endl;
                    cout << "Length of string: " << cp->info.Utf8.length << endl;
                    cout << "String: " << endl;
                    break;
                }
            }
        }

    }
}

void ClassFile::MenuInterfaces(){
    int opcao = -1;

    cout << "Interfaces" << endl;

    for(unsigned i = 0; i < this->interfaces_count; i++){
        // u2 interface = this->interfaces[i];
        
        cout << "[" << i+1 <<"] Interface" << endl;
    }

    while (opcao != 0){
        cout << endl << "Digite uma opcao: ";
        cin >> opcao;

        if(opcao-1 >= 0 && opcao-1 < this->interfaces_count){
            u2 interface = this->interfaces[opcao-1];
            CpInfo *cp = this->constant_pool[interface-1];
            u2 name_index = cp->info.Class.name_index;

            u1 *bytes = this->constant_pool[name_index-1]->info.Utf8.bytes;
            u2 length = this->constant_pool[name_index-1]->info.Utf8.length;
            // ReadFile::readByteString(bytes, length);

            cout << "Interface: cp_info #" << interface << " <" << (char*) bytes << ">" << endl;
        }
    }
}

void ClassFile::MenuFields(){
    int opcao = -1;

    cout << "Fields" << endl;

    for(unsigned i = 0; i < this->fields_count; i++){
        FieldInfo *field = this->fields[i];
        CpInfo *name = this->constant_pool[field->name_index-1];
        // CpInfo *descriptor = this->constant_pool[field->descriptor_index-1];
        // u2 access_flags = field->access_flags;
        
        cout << "[" << i+1 <<"] "<< name->info.Utf8.bytes << endl;
    }

    while (opcao != 0){
        cout << endl << "Digite uma opcao: ";
        cin >> opcao;

        if(opcao-1 >= 0 && opcao-1 < this->fields_count){
            FieldInfo *field = this->fields[opcao-1];
            CpInfo *name = this->constant_pool[field->name_index-1];
            CpInfo *descriptor = this->constant_pool[field->descriptor_index-1];
            u2 access_flags = field->access_flags;
            // ReadFile::readByteString(bytes, length);

            cout << "Name: cp_info #" << field->name_index << " <" << (char*) name->info.Utf8.bytes << ">" << endl;
            cout << "Descriptor: cp_info #" << field->descriptor_index << " <" << (char*) descriptor->info.Utf8.bytes << ">" << endl;
            cout << "Access flags: " << hex << access_flags << endl;
            cout << "Attribute count: " << dec << field->attributes_count << endl;
            
            this->PrintAttributes(field->attributes, field->attributes_count);

        }
    }
}

void ClassFile::MenuAttributes(){
    this->PrintAttributes(this->attributes, this->attributes_count);
}

void ClassFile::PrintAttributes(AttributeInfo * attributes, u2 attributes_count){
    for(unsigned i = 0; i < attributes_count; i++){
        CpInfo *attribute_name_index = this->constant_pool[attributes[i].attribute_name_index-1];
        
        u1 *bytes = attribute_name_index->info.Utf8.bytes;
        u2 length = attribute_name_index->info.Utf8.length;

        char array[length+1];
        memcpy(array, bytes , length);

        array[length] = '\0';

        string name = array;

        cout << "\t" << name << endl;
        cout << "\t\tAttribute name index: cp_info #" << dec << (int) attributes[i].attribute_name_index  << " <" << name << ">" << endl;
        cout << "\t\tAttribute length: " << dec << (int) attributes[i].attribute_length << endl;
        cout << "\t\tSpecific info ---------------------" << endl;
        
        if(name == "SourceFile")
        {
            u2 sourcefile_index = attributes[i].info.SourceFile.sourcefile_index;
            CpInfo *cp = this->constant_pool[sourcefile_index-1];

            // u2 string_index = cp->info.Utf8.;

            u1 *string_bytes = cp->info.Utf8.bytes;
            u2 string_length = cp->info.Utf8.length;

            char array[string_length+1];
            memcpy(array, string_bytes , string_length);

            array[string_length] = '\0';

            string string_name = array;

            cout << "\t\tSource file name index: cp_info #" << sourcefile_index << " <" << string_name << ">" << endl;            
        }
        else if(name == "ConstantValue"){
            u2 constantvalue_index = attributes[i].info.ConstantValue.constantvalue_index;
            CpInfo *cp = this->constant_pool[constantvalue_index-1];

            switch (cp->tag)
            {
                case CONSTANT_Integer:{
                    cout << "\t\tConstant value index: cp_info #" << constantvalue_index << " <" << dec << (int) cp->info.Integer.bytes << ">" << endl;
                    break;
                }
                case CONSTANT_String:{
                    u2 string_index = cp->info.String.string_index;

                    u1 *string_bytes = this->constant_pool[string_index-1]->info.Utf8.bytes;
                    u2 string_length = this->constant_pool[string_index-1]->info.Utf8.length;

                    char array[string_length+1];
                    memcpy(array, string_bytes , string_length);

                    array[string_length] = '\0';

                    string string_name = array;

                    cout << "\t\tConstant value index: cp_info #" << constantvalue_index << " <" << string_name << ">" << endl;
                    break;
                }
                case CONSTANT_Double:{
                    break;
                }
                case CONSTANT_Float:{
                    break;
                }
            }
        }
        else if(name == "InnerClasses")
        {
            Classes *classes = attributes[i].info.InnerClasses.classes;
            u2 number_of_classes = attributes[i].info.InnerClasses.number_of_classes;

            for(unsigned j = 0; j < number_of_classes; j++){
                u2 inner_class_info_index = classes[j].inner_class_info_index;
                u2 outer_class_info_index = classes[j].outer_class_info_index;
                u2 inner_name_index = classes[j].inner_name_index;
                u2 inner_class_access_flags = classes[j].inner_class_access_flags;

                cout << "Inner Class cp_info #" << inner_class_info_index << endl;
                cout << "Outer Class cp_info #" << outer_class_info_index << endl;
                cout << "Inner Class name index cp_info #" << inner_name_index << endl;
                cout << "Inner Class access flags " << hex << (int) inner_class_access_flags << endl;
                cout << endl;
            }
        } 
        else if (name == "Code"){
            u2 max_stack = attributes[i].info.Code.max_stack;
            u2 max_locals = attributes[i].info.Code.max_locals;
            u4 code_length = attributes[i].info.Code.code_length;

            u1 *code = attributes[i].info.Code.code;

            for (unsigned k = 0; k < attributes[i].info.Code.code_length; k++){
                u1 opcode = code[k];
            }

            u2 exception_table_length = attributes[i].info.Code.exception_table_length;
            
            ExceptionHandler *ExceptionTable = attributes[i].info.Code.exception_table;
            for (unsigned k = 0; k < exception_table_length; k++){
                u2 start_pc = ExceptionTable[k].start_pc;
                u2 end_pc = ExceptionTable[k].end_pc;
                u2 handler_pc = ExceptionTable[k].handler_pc;
                u2 catch_type = ExceptionTable[k].catch_type;
            }

            u2 attributes_count = attributes[i].info.Code.attributes_count;
            
            this->PrintAttributes(attributes[i].info.Code.attributes, attributes_count);
        }
        else if(name == "Exceptions"){
            u2 number_of_exceptions = attributes[i].info.Exceptions.number_of_exceptions;
            
            u2 *exception_index_table = attributes[i].info.Exceptions.exception_index_table;
            for(unsigned j = 0; j < number_of_exceptions; j++){

                // attributes[i].info.Exceptions.exception_index_table[j] = ReadFile::u2Read(file);
            }
        }
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
            u2 name_index = ReadFile::u2Read(file);
            u2 descriptor_index = ReadFile::u2Read(file);

            cp->info.NameAndType.name_index = name_index;
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

        AttributeInfo * attributes = this->CreateAttributeInfo(file, attributes_count);
        field->attributes = attributes;

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
