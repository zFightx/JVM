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
    setlocale(LC_ALL, "Portuguese");
    // ClassFile *cf = new ClassFile();
    // ifstream file("Simple.class", ios::binary);

    ClassFile *class_file = new ClassFile("Pig.class");

    class_file->MenuClassFile();

    u1 bytes[9] = {0x50, 0x69, 0x67, 0x73, 0xC3, 0x83, 0xC2, 0xA7, 0x61};
    ReadFile::readByteString(bytes, 9);

    return 0;
}