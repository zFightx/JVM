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
    // ifstream file("Simple.class", ios::binary);

    ClassFile *class_file = new ClassFile("Pig.class");
    

    delete class_file;

    return 0;
}