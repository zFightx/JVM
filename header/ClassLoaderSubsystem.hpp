#ifndef __Link_HPP__
#define __Link_HPP__

#include <iostream>
#include "Dados.hpp"
#include "ClassFile.hpp"

using namespace std;

class ClassLoaderSubsystem
{
public:
    static void verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName);
    static void prepare(ClassFile *cf);
    static void resolve(ClassFile *cf);
};

#endif