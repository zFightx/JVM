
#include <iostream>
#include <iomanip>
#include <fstream>

#include "header/ClassFile.hpp"
#include "header/Dados.hpp"
#include "header/ReadFile.hpp"
#include "header/Runtime.hpp"
#include "header/Interpreter.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");

    if (!argv[1] || !argv[2])
    {
        cerr << "\nArgumentos invalidos:\nPara inicializar a JVM, use os argumentos da seguinte forma:\n\nModo de uso: leitor ou interpretador.\nNome arquivo: arquivo a ser executado com .class no final\n\nExemplos:\n./main leitor Foo.class\n./main interpretador Foo.class" << endl;
        exit(-1);
    }

    string modo = argv[1];
    string file = argv[2];

    if (modo != "leitor" && modo != "interpretador")
    {
        cerr << "\nOs unicos modos permitidos sao leitor ou interpretador" << endl;
        exit(-1);
    }

    if (modo == "interpretador")
    {

        vector<Value> *args = new vector<Value>();
        for (unsigned i = 3; i < argc; i++)
        {
            Value value;
            value.type = STRING_VALUE;
            value.data.string_value = new string(argv[i]);
            args->push_back(value);
        }

        vector<Value> args_java;
        Value value;
        value.type = ARRAY_VALUE;
        value.data.array_value = args;
        args_java.push_back(value);

        Runtime *runtime = new Runtime(file, args_java);
        Interpreter *interpreter = new Interpreter(runtime);

        interpreter->ExecuteInterpreter();

        // cout << "aqui" << endl;
        delete runtime;
    }
    else{
        ClassFile *class_file = new ClassFile(file);
        class_file->MenuClassFile();
        delete class_file;
    }

    return 0;
}