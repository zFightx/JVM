#ifndef __Link_HPP__
#define __Link_HPP__

#include <iostream>
#include <map>

#include "Dados.hpp"
#include "ClassFile.hpp"
#include "MethodAreaSection.hpp"
#include "Runtime.hpp"

using namespace std;

class ClassLoaderSubsystem
{
public:
    static void Verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName);
    static void Prepare(ClassFile *cf);
    static void Resolve(string class_name, Runtime * runtime);

    static void Initialize(string class_name, ClassFile *class_file, Runtime *runtime);

    static string GetStringConstantPool(u2 index, vector<CpInfo *> constant_pool);
};

#endif