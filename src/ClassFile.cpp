#include "../header/ClassFile.hpp"
#include "../header/ReadFile.hpp"
#include "../header/AttributeInfo.hpp"

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

    this->magic = ReadFile::u4Read(file_stream);
    this->minor_version = ReadFile::u2Read(file_stream);
    this->major_version = ReadFile::u2Read(file_stream);
    this->constant_pool_count = ReadFile::u2Read(file_stream);

    // this->constant_pool = new CpInfo[this->constant_pool_count - 1];
    // read constant pool
    for (unsigned i = 0; i < this->constant_pool_count - 1; i++)
    {
        u1 tag = ReadFile::u1Read(file_stream);
        CpInfo *cp = new CpInfo(tag);

        this->constant_pool.push_back(cp);

        switch (tag)
        {
        case CONSTANT_Class:
        {
            u2 nameIndex = ReadFile::u2Read(file_stream);
            cp->info.Class.name_index = nameIndex;

            break;
        }
        case CONSTANT_Fieldref:
        {
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        }
        case CONSTANT_Methodref:
        {
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        }
        case CONSTANT_InterfaceMethodref:
        {
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        }
        case CONSTANT_NameAndType:
        {
            u2 class_index = ReadFile::u2Read(file_stream);
            u2 descriptor_index = ReadFile::u2Read(file_stream);
            // cout << "string index: " << hex << stringIndex << endl;
            break;
        }
        case CONSTANT_Utf8:
        {
            u2 lenght = ReadFile::u2Read(file_stream);
            u2 *bytes = new u2[(int)lenght];

            for (unsigned j = 0; j < lenght; j++)
            {
                bytes[j] = ReadFile::u2Read(file_stream);
            }

            // cout << "string index: " << hex << stringIndex << endl;
            break;
        }
        case CONSTANT_String:
        {
            u2 stringIndex = ReadFile::u2Read(file_stream);
            cout << "string index: " << hex << stringIndex << endl;
            break;
        }
        case CONSTANT_Integer:
        {
            cp->info.Integer.bytes = ReadFile::u4Read(file_stream);

            cout << "bytes: " << hex << cp->info.Integer.bytes << endl;
            break;
        }
        case CONSTANT_Float:
        {
            u4 bytes = ReadFile::u4Read(file_stream);
            break;
        }
        case CONSTANT_Long:
        {
            u4 high_bytes = ReadFile::u4Read(file_stream);
            u4 low_bytes = ReadFile::u4Read(file_stream);
            break;
        }
        case CONSTANT_Double:
        {
            u4 high_bytes = ReadFile::u4Read(file_stream);
            u4 low_bytes = ReadFile::u4Read(file_stream);
            break;
        }
        }
    }

    this->access_flags = ReadFile::u2Read(file_stream);
    this->this_class = ReadFile::u2Read(file_stream);
    this->super_class = ReadFile::u2Read(file_stream);

    this->interfaces_count = ReadFile::u2Read(file_stream);
    for (unsigned i = 0; i < this->interfaces_count; i++)
    {
        u2 interface = ReadFile::u2Read(file_stream);
        this->interfaces.push_back((int)interface);
    }

    this->fields_count = ReadFile::u2Read(file_stream);
    for (unsigned i = 0; i < this->fields_count; i++)
    {
        u2 access_flags = ReadFile::u2Read(file_stream);
        u2 name_index = ReadFile::u2Read(file_stream);
        u2 descriptor_index = ReadFile::u2Read(file_stream);
        u2 attributes_count = ReadFile::u2Read(file_stream);

        FieldInfo *field = new FieldInfo(access_flags, name_index, descriptor_index, attributes_count);

        for (unsigned j = 0; j < attributes_count; j++)
        {
            u2 attribute_name_index = ReadFile::u2Read(file_stream);
            u4 attribute_length = ReadFile::u4Read(file_stream);
            AttributeInfo *attribute = new AttributeInfo(attribute_name_index, attribute_length);
            attribute->info.ConstantValue.constantvalue_index = ReadFile::u2Read(file_stream);
            field->attributes.push_back(attribute);
        }

        this->fields.push_back(field);
    }
}