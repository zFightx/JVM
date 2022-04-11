
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
    
    string file = argv[1];

    vector<Value> *args = new vector<Value>();
    for(unsigned i = 2; i < argc; i++){
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

    cout << "aqui" << endl;
    delete runtime;

    return 0;
}