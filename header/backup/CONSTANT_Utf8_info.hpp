#ifndef __CONSTANT_Utf8_info_HPP__
#define __CONSTANT_Utf8_info_HPP__

#include "Dados.hpp"
#include "CpInfo.hpp"

class CONSTANT_Utf8_info : CpInfo{
    private: 
        u2 length;
        u2 *bytes;

    public:
        CONSTANT_Utf8_info();
};

#endif