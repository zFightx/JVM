#ifndef __CONSTANT_Double_info_HPP__
#define __CONSTANT_Double_info_HPP__

#include "Dados.hpp"
#include "CpInfo.hpp"

class CONSTANT_Double_info : CpInfo{
    private: 
        u4 high_bytes;
        u4 low_bytes;

    public:
        CONSTANT_Double_info();
};

#endif