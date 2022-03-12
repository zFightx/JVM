#include "../header/ReadFile.hpp"

#include <sstream>

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
