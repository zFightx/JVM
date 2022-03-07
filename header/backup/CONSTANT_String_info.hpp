#ifndef __CONSTANT_String_info_HPP__
#define __CONSTANT_String_info_HPP__

#include "Dados.hpp"
#include "CpInfo.hpp"

class CONSTANT_String_info : CpInfo{
    private: 
        u2 string_index;

    public:
        CONSTANT_String_info();
};

#endif