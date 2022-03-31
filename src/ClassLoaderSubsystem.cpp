#include <iostream>

#include "../header/ClassLoaderSubsystem.hpp"
#include "../header/Dados.hpp"
#include "../header/ClassFile.hpp"

using namespace std;

void ClassLoaderSubsystem::verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName)

{
    if (cafeBabe != 0xCAFEBABE)
    {
        throw "Invalid magic number!";
        // cout << "Invalid magic number" << endl;
        exit(1);
    }
    if (minorVersion != 0)
    {
        throw "Invalid minor version!";
        // cout << "Invalid minor version" << endl;
        exit(1);
    }
    if (majorVersion < 45 || majorVersion > 52)
    {
        throw "Invalid major version!";
        // cout << "Invalid major version" << endl;
        exit(1);
    }

    if (sourceFileFontName != fontName)
    {
        throw "Invalid source file name!";
        // cout << "Invalid source file name" << endl;
        exit(1);
    }
}

void ClassLoaderSubsystem::prepare(ClassFile *cf)
{
    // vector<CpInfo *> cp = cf->constant_pool;
    // vector<MethodInfo *> methods = cf->methods;
    // map <string, value>
}
