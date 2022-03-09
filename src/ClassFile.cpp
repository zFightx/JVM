#include "../header/ClassFile.hpp"
#include "../header/ReadFile.hpp"

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

    this->constant_pool = new CpInfo[this->constant_pool_count - 1];
    CpInfo *cp;
    // read constant pool
    for (cp = this->constant_pool; cp < this->constant_pool + constant_pool_count - 1; cp++)
    {
        cp->tag = ReadFile::u1Read(file_stream);
        cout << "tag: " << hex << (int)tag << endl;
        switch (tag)
        {
        case CONSTANT_Class:
            u2 nameIndex = ReadFile::u2Read(file_stream);

            break;
        case CONSTANT_String:
            u2 stringIndex = ReadFile::u2Read(file_stream);
            cout << "string index: " << hex << stringIndex << endl;
            break;
        case CONSTANT_Fieldref:
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_Methodref:
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_InterfaceMethodref:
            u2 classIndex = ReadFile::u2Read(file_stream);
            u2 nameAndTypeIndex = ReadFile::u2Read(file_stream);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_Integer:
            u4 bytes = ReadFile::u4Read(file_stream);
            cout << "bytes: " << hex << bytes << endl;
            break;
        case CONSTANT_Float:
        }