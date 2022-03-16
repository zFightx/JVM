
#include <iostream>
#include <iomanip>
#include <fstream>

#include "header/ClassFile.hpp"
#include "header/Dados.hpp"
#include "header/ReadFile.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    string file = "";
    cout << "Por favor, digite o nome do arquivo: ";
    cin >> file;
    ClassFile *class_file = new ClassFile(file);

    class_file->MenuClassFile();

    delete class_file;

    return 0;
}