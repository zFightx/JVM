#ifndef __ReadFile_HPP__
#define __ReadFile_HPP__

#include <iostream>
#include <fstream>

#include "Dados.hpp"

using namespace std;

class ReadFile
{
public:
    static u1 u1Read(ifstream &file);
    static u2 u2Read(ifstream &file);
    static u4 u4Read(ifstream &file);
    static u8 u8Read(ifstream &file);
};

#endif