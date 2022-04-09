#include <string.h>
#include <iostream>
#include <cmath>
#include <exception>

#include "../header/ClassFile.hpp"
#include "../header/ReadFile.hpp"
#include "../header/AttributeInfo.hpp"
#include "../header/ExceptionHandler.hpp"
#include "../header/Opcodes.hpp"

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

    file_stream.close();
}

ClassFile::~ClassFile()
{
    this->DeleteAttributes(this->attributes, this->attributes_count);

    for (unsigned i = 0; i < this->methods_count; i++)
    {
        this->DeleteAttributes(this->methods[i]->attributes, this->methods[i]->attributes_count);

        delete this->methods[i];
    }
    for (unsigned i = 0; i < this->fields_count; i++)
    {
        this->DeleteAttributes(this->fields[i]->attributes, this->fields[i]->attributes_count);
        delete this->fields[i];
    }

    for (unsigned i = 0; i < this->constant_pool_count - 1; i++)
    {
        delete this->constant_pool[i];
    }
}

void ClassFile::DeleteAttributes(AttributeInfo *attributes, u2 attributes_count)
{
    for (unsigned i = 0; i < attributes_count; i++)
    {
        u2 attribute_name_index = attributes[i].attribute_name_index;

        u1 *bytes = this->constant_pool[attribute_name_index - 1]->info.Utf8.bytes;
        u2 length = this->constant_pool[attribute_name_index - 1]->info.Utf8.length;

        string name = ReadFile::readByteString(bytes, length);

        if (name == "InnerClasses")
        {
            delete[] attributes[i].info.InnerClasses.classes;
        }
        else if (name == "Code")
        {
            this->DeleteAttributes(attributes[i].info.Code.attributes, attributes[i].info.Code.attributes_count);
            delete[] attributes[i].info.Code.code;
            delete[] attributes[i].info.Code.exception_table;
        }
        else if (name == "Exceptions")
        {
            delete[] attributes[i].info.Exceptions.exception_index_table;
        }
    }

    delete[] attributes;
}
//////////////////////////////////////////////////////////////////////////////////

void ClassFile::MenuClassFile()
{
    this->GeneralInformation();
    this->MenuConstantPool();
    this->MenuInterfaces();
    this->MenuFields();
    this->MenuMethodInfo();
    this->MenuAttributes();
}

void ClassFile::GeneralInformation()
{
    CpInfo *cp = this->constant_pool[this->this_class - 1];
    CpInfo *this_class = this->constant_pool[cp->info.Class.name_index - 1];

    string string_this_class = ReadFile::readByteString(this_class->info.Utf8.bytes, this_class->info.Utf8.length);
    string string_super_class = "invalid constant pool reference";

    if(this->super_class != 0){
        cp = this->constant_pool[this->super_class - 1];
        CpInfo *super_class = this->constant_pool[cp->info.Class.name_index - 1];
        string_super_class = ReadFile::readByteString(super_class->info.Utf8.bytes, super_class->info.Utf8.length);
    }

    float major_version = 1.1;

    switch (this->major_version)
    {
    case 45:
    {
        major_version = 1.1;
        break;
    }
    case 46:
    {
        major_version = 1.2;
        break;
    }
    case 47:
    {
        major_version = 1.3;
        break;
    }
    case 48:
    {
        major_version = 1.4;
        break;
    }
    case 49:
    {
        major_version = 1.5;
        break;
    }
    case 50:
    {
        major_version = 1.6;
        break;
    }
    case 51:
    {
        major_version = 1.7;
        break;
    }
    case 52:
    {
        major_version = 1.8;
        break;
    }
    case 53:
    {
        major_version = 9;
        break;
    }
    case 54:
    {
        major_version = 10;
        break;
    }
    case 55:
    {
        major_version = 11;
        break;
    }
    case 56:
    {
        major_version = 12;
        break;
    }
    case 57:
    {
        major_version = 13;
        break;
    }
    case 58:
    {
        major_version = 14;
        break;
    }
    case 59:
    {
        major_version = 15;
        break;
    }
    case 60:
    {
        major_version = 16;
        break;
    }
    }


    cout << "General Information" << endl
         << endl;
    cout << "\tMinor version: " << this->minor_version << endl;
    cout << "\tMajor version: " << dec << (int)this->major_version << " [" << major_version << "]" << endl;
    cout << "\tConstant pool count: " << this->constant_pool_count << endl;
    this->PrintAccessFlags(this->access_flags, CLASS);
    cout << "\tThis class: cp_info #" << this->this_class << " <" << string_this_class << ">" << endl;
    cout << "\tSuper class: cp_info #" << this->super_class << " <" << string_super_class << ">" << endl;
    cout << "\tInterfaces count: " << this->interfaces_count << endl;
    cout << "\tFields count: " << this->fields_count << endl;
    cout << "\tMethods count: " << this->methods_count << endl;
    cout << "\tAttributes count: " << this->attributes_count << endl;

    cout << endl;
}

void ClassFile::MenuConstantPool()
{

    cout << "Constant Pool" << endl;

    for (unsigned i = 0; i < this->constant_pool_count - 1; i++)
    {
        CpInfo *cp = this->constant_pool[i];
        switch (cp->tag)
        {
        case CONSTANT_Large:
        {
            cout << "\t[" << dec << i + 1 << "]"
                 << " (large numeric continued)" << endl;

            cout << endl;
            break;
        }
        case CONSTANT_Class:
        {
            cout << "\t[" << dec << i + 1 << "]"
                 << " CONSTANT_Class_info" << endl;

            u1 *bytes = this->constant_pool[cp->info.Class.name_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[cp->info.Class.name_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tClass name: cp_info #" << cp->info.Class.name_index << " <" << name << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Fieldref:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Fieldref_info" << endl;
            u2 class_name_index = this->constant_pool[cp->info.Fieldref.class_index - 1]->info.Class.name_index;
            u1 *bytes = this->constant_pool[class_name_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[class_name_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            u2 name_index = this->constant_pool[cp->info.Fieldref.name_and_type_index - 1]->info.NameAndType.name_index;
            u2 descriptor_index = this->constant_pool[cp->info.Fieldref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
            bytes = this->constant_pool[name_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[name_index - 1]->info.Utf8.length;
            string name_and_type = ReadFile::readByteString(bytes, length);

            bytes = this->constant_pool[descriptor_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[descriptor_index - 1]->info.Utf8.length;
            string descriptor = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tClass name: cp_info #" << cp->info.Fieldref.class_index << " <" << name
                 << ">" << endl;
            cout << "\t\tName and type: cp_info #" << cp->info.Fieldref.name_and_type_index << " <" << name_and_type << " : " << descriptor
                 << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Methodref:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Methodref_info" << endl;
            u2 class_name_index = this->constant_pool[cp->info.Methodref.class_index - 1]->info.Class.name_index;
            u1 *bytes = this->constant_pool[class_name_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[class_name_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            u2 name_index = this->constant_pool[cp->info.Methodref.name_and_type_index - 1]->info.NameAndType.name_index;
            u2 descriptor_index = this->constant_pool[cp->info.Methodref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
            bytes = this->constant_pool[name_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[name_index - 1]->info.Utf8.length;
            string name_and_type = ReadFile::readByteString(bytes, length);

            bytes = this->constant_pool[descriptor_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[descriptor_index - 1]->info.Utf8.length;
            string descriptor = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tClass name: cp_info #" << cp->info.Methodref.class_index << " <" << name
                 << ">" << endl;
            cout << "\t\tName and type: cp_info #" << cp->info.Methodref.name_and_type_index << " <" << name_and_type << " : " << descriptor
                 << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_InterfaceMethodref:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_InterfaceMethodref_info" << endl;

            u2 class_name_index = this->constant_pool[cp->info.InterfaceMethodref.class_index - 1]->info.Class.name_index;
            u1 *bytes = this->constant_pool[class_name_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[class_name_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            u2 name_index = this->constant_pool[cp->info.InterfaceMethodref.name_and_type_index - 1]->info.NameAndType.name_index;
            u2 descriptor_index = this->constant_pool[cp->info.InterfaceMethodref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
            bytes = this->constant_pool[name_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[name_index - 1]->info.Utf8.length;
            string name_and_type = ReadFile::readByteString(bytes, length);

            bytes = this->constant_pool[descriptor_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[descriptor_index - 1]->info.Utf8.length;
            string descriptor = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tClass name: cp_info #" << cp->info.InterfaceMethodref.class_index << " <" << name
                 << ">" << endl;
            cout << "\t\tName and type: cp_info #" << cp->info.InterfaceMethodref.name_and_type_index << " <" << name_and_type << " : " << descriptor
                 << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_String:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_String_info" << endl;

            u1 *bytes = this->constant_pool[cp->info.String.string_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[cp->info.String.string_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);
            // ReadFile::readByteString(bytes, length);
            // arrumar o cout

            cout << endl
                 << "\t\tString: cp_info #" << cp->info.String.string_index << " <" << name
                 << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Integer:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Integer_info" << endl;

            cout << endl
                 << "\t\tBytes: " << hex << (int)cp->info.Integer.bytes << endl;
            cout << "\t\tInteger: " << dec << (int)cp->info.Integer.bytes << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Float:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Float_info" << endl;

            int bits = (int)cp->info.Float.bytes;
            cout << endl
                 << "\t\tBytes: " << hex << bits << endl;

            if (bits == 0x7f800000)
            {
                cout << "\t\tFloat: "
                     << "+inf" << endl;
            }
            else if (bits == 0xff800000)
            {
                cout << "\t\tFloat: "
                     << "-inf" << endl;
            }
            else if ((bits >= 0x7f800001 && bits <= 0x7fffffff) || (bits >= 0xff800001 && bits <= 0xffffffff))
            {
                cout << "\t\tFloat: "
                     << "NaN" << endl;
            }
            else
            {
                int s = ((bits >> 31) == 0) ? 1 : -1;
                int e = ((bits >> 23) & 0xff);
                int m = (e == 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;

                float result = s * m * pow(2.0, e - 150);

                cout << "\t\tFloat: " << dec << (float)result << endl;
            }
            cout << endl;
            break;
        }
        case CONSTANT_Long:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Long_info" << endl;

            u4 high_bytes = cp->info.Long.high_bytes;
            u4 low_bytes = cp->info.Long.low_bytes;

            long long result = ((long long)high_bytes << 32) + low_bytes;

            cout << endl
                 << "\t\tHigh bytes: " << hex << (u4)high_bytes << endl;
            cout << "\t\tLow bytes: " << hex << (u4)low_bytes << endl;
            cout << "\t\tLong: " << dec << result << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Double:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Double_info" << endl;

            u4 high_bytes = cp->info.Double.high_bytes;
            u4 low_bytes = cp->info.Double.low_bytes;

            long long bits = ((long long)high_bytes << 32) + low_bytes;

            long s = ((bits >> 63) == 0) ? 1 : -1;
            long e = ((bits >> 52) & (long)0x7ffL);
            long long m = (e == 0) ? (bits & 0xfffffffffffffL) << 1 : (bits & 0xfffffffffffffL) | 0x10000000000000L;

            double result = s * m * pow(2, e - 1075);

            cout << endl
                 << "\t\tHigh bytes: 0x" << hex << (u4)high_bytes << endl;
            cout << "\t\tLow bytes: 0x" << hex << (u4)low_bytes << endl;
            cout << "\t\tDouble: " << dec << result << endl;
            cout << endl;
            break;
        }
        case CONSTANT_NameAndType:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_NameAndType_info" << endl;

            u1 *bytes = this->constant_pool[cp->info.NameAndType.name_index - 1]->info.Utf8.bytes;
            u2 length = this->constant_pool[cp->info.NameAndType.name_index - 1]->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            bytes = this->constant_pool[cp->info.NameAndType.descriptor_index - 1]->info.Utf8.bytes;
            length = this->constant_pool[cp->info.NameAndType.descriptor_index - 1]->info.Utf8.length;
            string descriptor = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tName: cp_info #" << cp->info.NameAndType.name_index << " <" << name
                 << ">" << endl;
            cout << "\t\tDescriptor: cp_info #" << cp->info.NameAndType.descriptor_index << " <" << descriptor
                 << ">" << endl;
            cout << endl;
            break;
        }
        case CONSTANT_Utf8:
        {
            cout << "\t[" << i + 1 << "]"
                 << " CONSTANT_Utf8_info" << endl;

            u1 *bytes = cp->info.Utf8.bytes;
            u2 length = cp->info.Utf8.length;
            string name = ReadFile::readByteString(bytes, length);

            cout << endl
                 << "\t\tLength of byte array: " << cp->info.Utf8.length << endl;
            cout << "\t\tLength of string: " << name.size() << endl;
            cout << "\t\tString: " << name << endl;
            cout << endl;
            break;
        }
        }
    }
}

void ClassFile::MenuInterfaces()
{

    cout << "Interfaces" << endl;

    for (unsigned i = 0; i < this->interfaces_count; i++)
    {
        cout << "\t[" << i + 1 << "] Interface" << endl;

        u2 interface = this->interfaces[i];
        CpInfo *cp = this->constant_pool[interface - 1];
        u2 name_index = cp->info.Class.name_index;

        u1 *bytes = this->constant_pool[name_index - 1]->info.Utf8.bytes;
        u2 length = this->constant_pool[name_index - 1]->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        cout << "\t\tInterface: cp_info #" << interface << " <" << name << ">" << endl;
        cout << endl;
    }
}

void ClassFile::MenuFields()
{

    cout << "Fields" << endl;

    for (unsigned i = 0; i < this->fields_count; i++)
    {
        FieldInfo *field = this->fields[i];
        CpInfo *name = this->constant_pool[field->name_index - 1];
        string field_name = ReadFile::readByteString(name->info.Utf8.bytes, name->info.Utf8.length);
        CpInfo *descriptor = this->constant_pool[field->descriptor_index - 1];
        u2 access_flags = field->access_flags;
        string field_descriptor = ReadFile::readByteString(descriptor->info.Utf8.bytes, descriptor->info.Utf8.length);

        cout << "[" << i << "] " << field_name << endl;

        cout << "\tName: cp_info #" << field->name_index << " <" << field_name << ">" << endl;
        cout << "\tDescriptor: cp_info #" << field->descriptor_index << " <" << field_descriptor << ">" << endl;
        this->PrintAccessFlags(access_flags, FIELD);
        cout << "\tAttribute count: " << dec << field->attributes_count << endl;

        this->PrintAttributes(field->attributes, field->attributes_count);
        cout << endl;
    }
}

void ClassFile::MenuMethodInfo()
{
    vector<CpInfo *> constant_pool = this->constant_pool;
    vector<MethodInfo *> methods = this->methods;
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;

    CpInfo *utf8;
    u1 *bytes;
    u2 length;
    string name;
    string descriptor;

    int methods_count = this->methods_count;

    cout << "----Methods----" << endl
         << endl;

    for (unsigned i = 0; i < methods_count; i++)
    {
        name_index = methods[i]->name_index;
        utf8 = constant_pool[name_index - 1];
        bytes = utf8->info.Utf8.bytes;
        length = utf8->info.Utf8.length;
        name = ReadFile::readByteString(bytes, length);
        cout << "\t[" << i << "] " << name << endl;

        MethodInfo *selectedMethod = methods[i];
        access_flags = selectedMethod->access_flags;

        name_index = selectedMethod->name_index;
        utf8 = constant_pool[name_index - 1];
        bytes = utf8->info.Utf8.bytes;
        length = utf8->info.Utf8.length;
        name = ReadFile::readByteString(bytes, length);

        descriptor_index = selectedMethod->descriptor_index;
        utf8 = constant_pool[descriptor_index - 1];
        bytes = utf8->info.Utf8.bytes;
        length = utf8->info.Utf8.length;
        descriptor = ReadFile::readByteString(bytes, length);

        attributes_count = selectedMethod->attributes_count;

        this->PrintAccessFlags(access_flags, METHOD);
        cout << "\tName: cp_info #" << name_index << " <" << name << ">" << endl;
        cout << "\tDescriptor: cp_info #" << descriptor_index << " " << descriptor << endl;

        this->PrintAttributes(selectedMethod->attributes, attributes_count);
    }
    cout << endl;
}

void ClassFile::MenuAttributes()
{
    cout << "Attributes" << endl;
    this->PrintAttributes(this->attributes, this->attributes_count);
}

void ClassFile::PrintAccessFlags(u2 access_flags, int flagType)
{

    string access_flags_string = "";

    cout << "\tAccess flags: 0x";
    printf("%04x", access_flags);

    for (int i = 0; i < 16; i++)
    {
        u2 flagBit = access_flags & (0x0001 << i);

        if (!access_flags_string.empty() && access_flags_string.back() != ' ')
        {
            access_flags_string += " ";
        }

        switch (flagBit)
        {
        case 0x0001:
        {
            access_flags_string += "public";
            break;
        }
        case 0x0002:
        {
            access_flags_string += "private";
            break;
        }
        case 0x0004:
        {
            access_flags_string += "protected";
            break;
        }
        case 0x0008:
        {
            access_flags_string += "static";
            break;
        }
        case 0x0010:
        {
            access_flags_string += "final";
            break;
        }
        case 0x0020:
        {
            switch (flagType)
            {
            case CLASS:

                access_flags_string += "super";
                break;

            case METHOD:

                access_flags_string += "synchronized";
                break;
            }
            break;
        }
        case 0x0040:
        {
            switch (flagType)
            {
            case FIELD:
                access_flags_string += "volatile";
                break;

            case METHOD:
                access_flags_string += "bridge";
                break;
            }
        }
        case 0x0080:
        {
            switch (flagType)
            {
            case FIELD:
                access_flags_string += "transient";
                break;

            case METHOD:
                access_flags_string += "varargs";
                break;
            }
        }
        case 0x0100:
        {
            access_flags_string += "native";
            break;
        }
        case 0x0200:
        {
            access_flags_string += "interface";
            break;
        }
        case 0x0400:
        {
            access_flags_string += "abstract";
            break;
        }
        case 0x0800:
        {
            access_flags_string += "strict";
            break;
        }
        case 0x1000:
        {
            access_flags_string += "synthetic";
            break;
        }
        case 0x2000:
        {
            access_flags_string += "annotation";
            break;
        }
        case 0x4000:
        {
            access_flags_string += "enum";
            break;
        }
        }
    }

    if (!access_flags_string.empty() && access_flags_string.back() == ' ')
    {
        access_flags_string.pop_back();
    }
    cout << " [" << access_flags_string << "]" << endl;
}

void ClassFile::PrintAttributes(AttributeInfo *attributes, u2 attributes_count)
{
    for (unsigned i = 0; i < attributes_count; i++)
    {
        CpInfo *attribute_name_index = this->constant_pool[attributes[i].attribute_name_index - 1];

        u1 *bytes = attribute_name_index->info.Utf8.bytes;
        u2 length = attribute_name_index->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        cout << "\t" << name << endl;
        cout << "\t\tAttribute name index: cp_info #" << dec << (int)attributes[i].attribute_name_index << " <" << name << ">" << endl;
        cout << "\t\tAttribute length: " << dec << (int)attributes[i].attribute_length << endl;

        if (name != "LineNumberTable" && name != "LocalVariableTable")
        {
            cout << "\t\tSpecific info ---------------------" << endl;
        }
        else
        {
            cout << endl;
        }

        if (name == "SourceFile")
        {
            u2 sourcefile_index = attributes[i].info.SourceFile.sourcefile_index;
            CpInfo *cp = this->constant_pool[sourcefile_index - 1];

            u1 *string_bytes = cp->info.Utf8.bytes;
            u2 string_length = cp->info.Utf8.length;
            string string_name = ReadFile::readByteString(string_bytes, string_length);

            cout << "\t\tSource file name index: cp_info #" << sourcefile_index << " <" << string_name << ">" << endl;
        }
        else if (name == "ConstantValue")
        {
            u2 constantvalue_index = attributes[i].info.ConstantValue.constantvalue_index;
            CpInfo *cp = this->constant_pool[constantvalue_index - 1];

            switch (cp->tag)
            {
            case CONSTANT_Integer:
            {
                cout << "\t\tConstant value index: cp_info #" << constantvalue_index << " <" << dec << (int)cp->info.Integer.bytes << ">" << endl;
                break;
            }
            case CONSTANT_String:
            {
                u2 string_index = cp->info.String.string_index;

                u1 *string_bytes = this->constant_pool[string_index - 1]->info.Utf8.bytes;
                u2 string_length = this->constant_pool[string_index - 1]->info.Utf8.length;
                string string_name = ReadFile::readByteString(string_bytes, string_length);

                cout << "\t\tConstant value index: cp_info #" << constantvalue_index << " <" << string_name << ">" << endl;
                break;
            }
            case CONSTANT_Double:
            {
                break;
            }
            case CONSTANT_Float:
            {
                break;
            }
            }
        }
        else if (name == "InnerClasses")
        {
            Classes *classes = attributes[i].info.InnerClasses.classes;
            u2 number_of_classes = attributes[i].info.InnerClasses.number_of_classes;

            for (unsigned j = 0; j < number_of_classes; j++)
            {
                u2 inner_class_info_index = classes[j].inner_class_info_index;
                u2 outer_class_info_index = classes[j].outer_class_info_index;
                u2 inner_name_index = classes[j].inner_name_index;
                u2 inner_class_access_flags = classes[j].inner_class_access_flags;

                cout << "Inner Class cp_info #" << inner_class_info_index << endl;
                cout << "Outer Class cp_info #" << outer_class_info_index << endl;
                cout << "Inner Class name index cp_info #" << inner_name_index << endl;
                cout << "Inner Class ";
                this->PrintAccessFlags(inner_class_access_flags, ATTRIBUTE);
                cout << endl;
            }
        }
        else if (name == "Code")
        {
            u2 max_stack = attributes[i].info.Code.max_stack;
            u2 max_locals = attributes[i].info.Code.max_locals;
            u4 code_length = attributes[i].info.Code.code_length;

            u1 *code = attributes[i].info.Code.code;

            cout << endl
                 << "\t\t----Bytecode---- " << endl;

            Opcodes::PrintOpcodes(code, code_length, this->constant_pool);

            u2 exception_table_length = attributes[i].info.Code.exception_table_length;

            ExceptionHandler *ExceptionTable = attributes[i].info.Code.exception_table;
            cout << "\t\t----Exeption Table----" << endl;
            for (unsigned k = 0; k < exception_table_length; k++)
            {
                u2 start_pc = ExceptionTable[k].start_pc;
                u2 end_pc = ExceptionTable[k].end_pc;
                u2 handler_pc = ExceptionTable[k].handler_pc;
                u2 catch_type = ExceptionTable[k].catch_type;
                cout << "\t\tNr\t"
                     << "Start PC\t"
                     << "End Pc\t"
                     << "Handler PC\t"
                     << "   Catch Type   " << endl;
                cout << k + 1 << "\t" << start_pc << "\t" << end_pc << "\t" << handler_pc << "\t" << catch_type << endl;
            }

            cout << endl
                 << "\t\t----Misc----" << endl;
            cout << "\t\tMax stack: " << dec << max_stack << endl;
            cout << "\t\tMax locals: " << dec << max_locals << endl;
            cout << "\t\tCode length: " << dec << code_length << endl;

            u2 attributes_count = attributes[i].info.Code.attributes_count;
            cout << endl;
            this->PrintAttributes(attributes[i].info.Code.attributes, attributes_count);
        }
        else if (name == "Exceptions")
        {
            u2 number_of_exceptions = attributes[i].info.Exceptions.number_of_exceptions;

            u2 *exception_index_table = attributes[i].info.Exceptions.exception_index_table;
            for (unsigned j = 0; j < number_of_exceptions; j++)
            {
                u2 exception_index = exception_index_table[j];
                CpInfo *class_info = this->constant_pool[exception_index - 1];
                u2 name_index = class_info->info.Class.name_index;
                u1 *class_name_bytes = this->constant_pool[name_index - 1]->info.Utf8.bytes;
                u2 class_name_length = this->constant_pool[name_index - 1]->info.Utf8.length;
                cout << "\t\tException index: cp_info #" << exception_index_table[j] << " <" << ReadFile::readByteString(class_name_bytes, class_name_length) << ">" << endl;
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

            CpInfo *large = new CpInfo(0);
            this->constant_pool.push_back(large);
            i++;

            break;
        }
        case CONSTANT_Double:
        {
            u4 high_bytes = ReadFile::u4Read(file);
            u4 low_bytes = ReadFile::u4Read(file);

            cp->info.Double.high_bytes = high_bytes;
            cp->info.Double.low_bytes = low_bytes;

            CpInfo *large = new CpInfo(0);
            this->constant_pool.push_back(large);
            i++;

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

        AttributeInfo *attributes = this->CreateAttributeInfo(file, attributes_count);
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

        AttributeInfo *attributes = CreateAttributeInfo(file, attributes_count);
        method->attributes = attributes;

        this->methods.push_back(method);
    }
}

AttributeInfo *ClassFile::CreateAttributeInfo(ifstream &file, u2 attributes_count)
{

    AttributeInfo *attributes = new AttributeInfo[attributes_count];

    for (unsigned i = 0; i < attributes_count; i++)
    {
        u2 attribute_name_index = ReadFile::u2Read(file);
        u4 attribute_length = ReadFile::u4Read(file);

        attributes[i] = AttributeInfo(attribute_name_index, attribute_length);

        u1 *bytes = this->constant_pool[attribute_name_index - 1]->info.Utf8.bytes;
        u2 length = this->constant_pool[attribute_name_index - 1]->info.Utf8.length;

        string name = ReadFile::readByteString(bytes, length);

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
    }
    return attributes;
}

MethodInfo* ClassFile::getMethodByName(string name){
    for(unsigned i = 0; i < this->methods_count; i++){
        MethodInfo *method = this->methods[i];
        string method_name = ReadFile::readString(method->name_index, this->constant_pool);
        if(method_name == name){
            return method;
        }
    }
    return NULL;
}
