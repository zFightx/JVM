#ifndef __ReadFile_HPP__
#define __ReadFile_HPP__

#include <iostream>
#include <fstream>

#include "Dados.hpp"
#include "CpInfo.hpp"

using namespace std;

class ReadFile
{
public:
    static u1 u1Read(ifstream &file);
    static u2 u2Read(ifstream &file);
    static u4 u4Read(ifstream &file);
    static u8 u8Read(ifstream &file);

    static string readByteString(u1 *bytes, u2 length);
    static pair<string, vector<string>> readStringPair(int index, vector<CpInfo *> constant_pool);
    static string readString(int index, vector<CpInfo *> constantPool);
    static vector<string> readString(int index, vector<CpInfo *> constantPool, bool vectorRet);

    static int16_t getCodeShort(u1 *code, int i);
    static uint16_t getCodeUShort(u1 *code, int i);
    static int32_t getCodeInt(u1 *code, int i);
};

#endif