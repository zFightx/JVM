#ifndef __Interpreter_HPP__
#define __Interpreter_HPP__

#include <map>

#include "Dados.hpp"
#include "Runtime.hpp"

using namespace std;

class Interpreter
{
public:
    map<u1, void *> instruction_table;

    Interpreter();
    ~Interpreter();

    void Interpret(Runtime *runtime);
};

#endif