#ifndef __Link_HPP__
#define __Link_HPP__

#include <iostream>
#include "Dados.hpp"
#include "ClassFile.hpp"

using namespace std;

class Link
{
public:
    static void verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName);
    static void prepare(CpInfo *cp);
    static void resolve();
};

#endif