#include <iostream>
#include <iomanip>
#include <fstream>
#include "header/ClassFile.hpp"
#include "header/Dados.hpp"
#include "header/ReadFile.hpp"

using namespace std;

// read and print binary file in hex
void printBinaryFile(string fileName)
{
    ifstream file(fileName, ios::binary);
    if (!file.is_open())
    {
        cout << "Error: file not found" << endl;
        return;
    }
    u1 byte;
    int i = 0;
    while (file.read((char *)&byte, sizeof(u1)))
    {
        cout << setfill('0') << setw(2) << hex << (int)byte << " ";
        i++;
        if (i % 16 == 0)
        {
            cout << endl;
        }
    }
    file.close();
}

int main()
{
    // ClassFile *cf = new ClassFile();
    ifstream file("Simple.class", ios::binary);

    file.seekg(0, ios::beg);

    u4 magic = ReadFile::u4Read(file);
    u2 minorVersion = ReadFile::u2Read(file);
    u2 majorVersion = ReadFile::u2Read(file);
    u2 constantPoolCount = ReadFile::u2Read(file);

    cout << "magic: " << hex << (int)magic << endl;
    cout << "minor version: " << hex << minorVersion << endl;
    cout << "major version: " << hex << majorVersion << endl;
    cout << "constant pool count: " << hex << constantPoolCount << endl;

    // read constant pool
    for (int i = 0; i < constantPoolCount; i++)
    {
        u1 tag = u1Read(file);
        cout << "tag: " << hex << (int)tag << endl;
        switch (tag)
        {
        case CONSTANT_Class:
            u2 nameIndex = u2Read(file);
            cout << "name index: " << hex << nameIndex << endl;
            break;
        case CONSTANT_Fieldref:
            u2 classIndex = u2Read(file);
            u2 nameAndTypeIndex = u2Read(file);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_Methodref:
            u2 classIndex = u2Read(file);
            u2 nameAndTypeIndex = u2Read(file);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_InterfaceMethodref:
            u2 classIndex = u2Read(file);
            u2 nameAndTypeIndex = u2Read(file);
            cout << "class index: " << hex << classIndex << endl;
            cout << "name and type index: " << hex << nameAndTypeIndex << endl;
            break;
        case CONSTANT_String:
            u2 stringIndex = u2Read(file);
            cout << "string index: " << hex << stringIndex << endl;
            break;
        case CONSTANT_Integer:
            u4 bytes4 = u4Read(file);
            cout << "bytes4: " << hex << bytes4 << endl;
            break;
        case CONSTANT_Float:
            u4 bytes4 = u4Read(file);
            cout << "bytes4: " << hex << bytes4 << endl;
            break;
        case CONSTANT_Long:
            u8 bytes8 = u

                return 0;
        }