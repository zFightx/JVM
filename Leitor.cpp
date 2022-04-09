
#include <iostream>
#include <iomanip>
#include <fstream>

#include "header/ClassFile.hpp"
#include "header/Dados.hpp"
#include "header/ReadFile.hpp"
#include "header/Runtime.hpp"
#include "header/Interpreter.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    string file = "";
    cout << "Por favor, digite o nome do arquivo: ";
    cin >> file;
    // ClassFile *class_file = new ClassFile(file);

    // class_file->MenuClassFile();

    // delete class_file;

    Runtime *runtime = new Runtime(file);
    Interpreter *interpreter = new Interpreter(runtime);

    interpreter->ExecuteInterpreter();

    cout << "aqui" << endl;
    delete runtime;

    return 0;
}