#include "../header/MethodAreaSection.hpp"
#include "../header/ReadFile.hpp"

using namespace std;

MethodAreaSection::MethodAreaSection(ClassFile *cf)
{
    this->constant_pool = cf->constant_pool;
    this->methods = cf->methods;

    map<string, value> &variables = this->variables;

    for (int i = 0; i < cf->fields.size(); i++)
    {
        FieldInfo *field = cf->fields[i];

        string name = ReadFile::readString(field->name_index, this->constant_pool);
        string descriptor = ReadFile::readString(field->descriptor_index, this->constant_pool);
        u2 staticFlag = 0x0008;
        u2 finalFlag = 0x0010;

        if ((field->access_flags & staticFlag) != 0 && (field->access_flags & finalFlag) == 0)
        {
            value value;
            char type = descriptor[0];
            value.type = type;

            switch (type)
            {
            case 'B':
                value.data.byteValue = 0;
                break;
            case 'C':
                value.data.charValue = 0;
                break;
            case 'D':
                value.data.doubleValue = 0;
                break;
            case 'F':
                value.data.floatValue = 0;
                break;
            case 'I':
                value.data.intValue = 0;
                break;
            case 'J':
                value.data.longValue = 0;
                break;
            case 'L':
                value.data.objectValue = NULL;
                break;
            case 'S':
                value.data.shortValue = 0;
                break;
            case 'Z':
                value.data.booleanValue = false;
                break;
            case '[':
                value.data.arrayValue = NULL;
                break;
            }

            variables[name] = value;
        }
    }
}
