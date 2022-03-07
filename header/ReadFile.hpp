#ifndef __ReadFile_HPP__
#define __ReadFile_HPP__

#include <iostream>
#include <fstream>

#include "Dados.hpp"

using namespace std;

class ReadFile
{
    public:
        static u1 u1Read(fstream &file);
        static u2 u2Read(fstream &file);
        static u4 u4Read(fstream &file);
        static u8 u8Read(fstream &file);
};


#endif