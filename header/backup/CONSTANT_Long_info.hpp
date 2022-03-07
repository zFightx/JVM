#ifndef __CONSTANT_Float_info_HPP__
#define __CONSTANT_Float_info_HPP__

#include "Dados.hpp"
#include "CpInfo.hpp"

class CONSTANT_Float_info : CpInfo{
    private: 
        u4 high_bytes;
        u4 low_bytes;

    public:
        CONSTANT_Float_info();
};

#endif