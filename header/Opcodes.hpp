#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include <iostream>
#include <vector>
#include <map>
#include "Dados.hpp"

using namespace std;

class Opcodes{
    public: 
        static map<int, pair<string, int> > opcodes;

        static void CreateOpcodes();


};

#endif