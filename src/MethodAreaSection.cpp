#include "../header/MethodAreaSection.hpp"
#include "../header/ReadFile.hpp"

using namespace std;

MethodAreaSection::MethodAreaSection(ClassFile *cf)
{
    this->class_file = cf;
}
