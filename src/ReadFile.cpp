#include "../header/ReadFile.hpp"
#include "../header/Dados.hpp"

#include <sstream>
#include <cmath>

u1 ReadFile::u1Read(ifstream &file)
{
    u1 u1;
    file.read((char *)&u1, sizeof(u1));
    return u1;
}

u2 ReadFile::u2Read(ifstream &file)
{
    u2 u2;
    file.read((char *)&u2, sizeof(u2));
    u2 = ((u2 & 0xFF) << 8) | ((u2 & 0xFF00) >> 8); // swap bytes to big endian
    // cout << "u2Read: " << hex << u2 << endl;
    return u2;
}

u4 ReadFile::u4Read(ifstream &file)
{
    u4 bytes4;
    file.read((char *)&bytes4, sizeof(bytes4));

    // swap bytes to big endian
    u4 leftmostByte = (bytes4 & 0xFF) << 24;
    u4 leftMiddleByte = (bytes4 & 0x0000FF00) << 8;
    u4 rightMiddleByte = (bytes4 & 0x00FF0000) >> 8;
    u4 rightmostByte = (bytes4 & 0xFF000000) >> 24;
    u4 result = leftmostByte | leftMiddleByte | rightMiddleByte | rightmostByte;

    // cout << "bytes4: " << hex << result << endl;
    return result;
}

u8 ReadFile::u8Read(ifstream &file)
{
    u8 bytes8 = 0x00;
    // file.read((char *)&bytes8, 8);
    u1 byte;

    for (int i = 0; i < 8; i++)
    {
        byte = u1Read(file);
        bytes8 = (bytes8 << 8) | byte;
    }
    // cout << "bytes8: " << hex << bytes8 << endl;

    return bytes8;
}

string ReadFile::readByteString(u1 *bytes, u2 length)
{
    stringstream ss;
    int strLength = length + 1;
    int stringIndex = 0;
    char *str = new char[strLength];
    for (int i = 0; i < length; i++)
    {
        u1 discriminatorBit = (bytes[i] & 0xFF) >> 4;
        if (discriminatorBit <= 0x07)
        {

            str[stringIndex] = bytes[i];
            stringIndex++;
        }
        else if (discriminatorBit <= 0x0D)
        {

            u1 xbyte = bytes[i];
            u1 ybyte = bytes[i + 1];
            i++;
            int x = (xbyte & 0x1F) << 6;
            int y = (ybyte & 0x3F);
            u1 character = x + y;
            str[stringIndex] = character;
            stringIndex++;
        }
        else if (discriminatorBit <= 0x0E)
        {

            u1 xbyte = bytes[i];
            u1 ybyte = bytes[i + 1];
            u1 zbyte = bytes[i + 2];
            i = i + 2;
            char16_t character = ((xbyte & 0x0F) << 12) + ((ybyte & 0x3F) << 6);
            character += zbyte & 0x3F;
            str[stringIndex] = character;
            stringIndex++;
        }
    }
    str[length] = '\0';

    return str;
}

string ReadFile::readString(int index, vector<CpInfo *> constant_pool)
{
    CpInfo *constant_info = constant_pool[index - 1];
    u1 tag = constant_info->tag;
    u1 *bytes;
    u2 length;
    string str;

    switch (tag)
    {
    case CONSTANT_Class:
    {
        bytes = constant_info->info.Utf8.bytes;
        length = constant_info->info.Utf8.length;
        str = ReadFile::readByteString(bytes, length);
        break;
    }
    case CONSTANT_Fieldref:
    {
        u2 class_name_index = constant_pool[constant_info->info.Fieldref.class_index - 1]->info.Class.name_index;
        u1 *bytes = constant_pool[class_name_index - 1]->info.Utf8.bytes;
        u2 length = constant_pool[class_name_index - 1]->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        u2 name_index = constant_pool[constant_info->info.Fieldref.name_and_type_index - 1]->info.NameAndType.name_index;
        u2 descriptor_index = constant_pool[constant_info->info.Fieldref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
        bytes = constant_pool[name_index - 1]->info.Utf8.bytes;
        length = constant_pool[name_index - 1]->info.Utf8.length;
        string name_and_type = ReadFile::readByteString(bytes, length);

        bytes = constant_pool[descriptor_index - 1]->info.Utf8.bytes;
        length = constant_pool[descriptor_index - 1]->info.Utf8.length;
        string descriptor = ReadFile::readByteString(bytes, length);

        str = name + "." + name_and_type + " : " + descriptor;
        break;
    }
    case CONSTANT_Methodref:
    {

        u2 class_name_index = constant_pool[constant_info->info.Methodref.class_index - 1]->info.Class.name_index;
        u1 *bytes = constant_pool[class_name_index - 1]->info.Utf8.bytes;
        u2 length = constant_pool[class_name_index - 1]->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        u2 name_index = constant_pool[constant_info->info.Methodref.name_and_type_index - 1]->info.NameAndType.name_index;
        u2 descriptor_index = constant_pool[constant_info->info.Methodref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
        bytes = constant_pool[name_index - 1]->info.Utf8.bytes;
        length = constant_pool[name_index - 1]->info.Utf8.length;
        string name_and_type = ReadFile::readByteString(bytes, length);

        bytes = constant_pool[descriptor_index - 1]->info.Utf8.bytes;
        length = constant_pool[descriptor_index - 1]->info.Utf8.length;
        string descriptor = ReadFile::readByteString(bytes, length);

        str = name + "." + name_and_type + " : " + descriptor;
        break;
    }
    case CONSTANT_InterfaceMethodref:
    {
        u2 class_name_index = constant_pool[constant_info->info.InterfaceMethodref.class_index - 1]->info.Class.name_index;
        u1 *bytes = constant_pool[class_name_index - 1]->info.Utf8.bytes;
        u2 length = constant_pool[class_name_index - 1]->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        u2 name_index = constant_pool[constant_info->info.InterfaceMethodref.name_and_type_index - 1]->info.NameAndType.name_index;
        u2 descriptor_index = constant_pool[constant_info->info.InterfaceMethodref.name_and_type_index - 1]->info.NameAndType.descriptor_index;
        bytes = constant_pool[name_index - 1]->info.Utf8.bytes;
        length = constant_pool[name_index - 1]->info.Utf8.length;
        string name_and_type = ReadFile::readByteString(bytes, length);

        bytes = constant_pool[descriptor_index - 1]->info.Utf8.bytes;
        length = constant_pool[descriptor_index - 1]->info.Utf8.length;
        string descriptor = ReadFile::readByteString(bytes, length);

        str = name + "." + name_and_type + " : " + descriptor;

        break;
    }
    case CONSTANT_String:
    {
        u2 string_index = constant_info->info.String.string_index;
        u1 *bytes = constant_pool[string_index - 1]->info.Utf8.bytes;
        u2 length = constant_pool[string_index - 1]->info.Utf8.length;
        str = ReadFile::readByteString(bytes, length);
        break;
    }
    case CONSTANT_Integer:
    {
        u4 value = (int)constant_info->info.Integer.bytes;
        str = to_string(value);
        break;
    }
    case CONSTANT_Float:
    {
        int bits = (int)constant_info->info.Float.bytes;

        if (bits == 0x7f800000)
        {
            str = "+inf";
        }
        else if (bits == 0xff800000)
        {

            str = "-inf";
        }
        else if ((bits >= 0x7f800001 && bits <= 0x7fffffff) || (bits >= 0xff800001 && bits <= 0xffffffff))
        {
            str = "NaN";
        }
        else
        {
            int s = ((bits >> 31) == 0) ? 1 : -1;
            int e = ((bits >> 23) & 0xff);
            int m = (e == 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;

            float result = s * m * pow(2.0, e - 150);

            str = to_string((float)result);
        }
        break;
    }
    case CONSTANT_Long:
    {
        u4 high_bytes = constant_info->info.Long.high_bytes;
        u4 low_bytes = constant_info->info.Long.low_bytes;

        long long value = ((long long)high_bytes << 32) + low_bytes;

        str = to_string(value);
        
        break;
    }
    case CONSTANT_Double:
    {
        u4 high_bytes = constant_info->info.Double.high_bytes;
        u4 low_bytes = constant_info->info.Double.low_bytes;

        long long bits = ((long long)high_bytes << 32) + low_bytes;

        long s = ((bits >> 63) == 0) ? 1 : -1;
        long e = ((bits >> 52) & (long)0x7ffL);
        long long m = (e == 0) ? (bits & 0xfffffffffffffL) << 1 : (bits & 0xfffffffffffffL) | 0x10000000000000L;

        double result = s * m * pow(2, e - 1075);

        str = to_string(result);

        break;
    }
    case CONSTANT_NameAndType:{
        u2 name_index = constant_info->info.NameAndType.name_index;
        u2 descriptor_index = constant_info->info.NameAndType.descriptor_index;
        u1 *bytes = constant_pool[name_index - 1]->info.Utf8.bytes;
        u2 length = constant_pool[name_index - 1]->info.Utf8.length;
        string name = ReadFile::readByteString(bytes, length);

        bytes = constant_pool[descriptor_index - 1]->info.Utf8.bytes;
        length = constant_pool[descriptor_index - 1]->info.Utf8.length;
        string descriptor = ReadFile::readByteString(bytes, length);

        str = name + " : " + descriptor;
        break;

    }
    case CONSTANT_Utf8:{
        u1 *bytes = constant_info->info.Utf8.bytes;
        u2 length = constant_info->info.Utf8.length;
        str = ReadFile::readByteString(bytes, length);
        break;
    }

}
    return str;
}

int16_t ReadFile::getCodeShort(u1 *code, int i )
{
    u1 byte1 = code[i + 1];
    u1 byte2 = code[i + 2];
    int16_t value = (byte1 << 8) | byte2;
    return value;
}

uint16_t ReadFile::getCodeUShort(u1 *code, int i )
{
    u1 byte1 = code[i + 1];
    u1 byte2 = code[i + 2];
    uint16_t value = (byte1 << 8) | byte2;
    return value;
}

int32_t ReadFile::getCodeInt(u1 *code, int i )
{
    u1 byte1 = code[i + 1];
    u1 byte2 = code[i + 2];
    u1 byte3 = code[i + 3];
    u1 byte4 = code[i + 4];
    int32_t value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    return value;
}
