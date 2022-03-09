#include "../header/ReadFile.hpp"

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
    cout << "u2Read: " << hex << u2 << endl;
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

    cout << "bytes4: " << hex << result << endl;
    return bytes4;
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
    cout << "bytes8: " << hex << bytes8 << endl;

    return bytes8;
}