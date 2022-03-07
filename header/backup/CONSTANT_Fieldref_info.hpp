#ifndef __CONSTANT_Fieldref_info_HPP__
#define __CONSTANT_Fieldref_info_HPP__

#include "Dados.hpp"
#include "CpInfo.hpp"

class CONSTANT_Fieldref_info : CpInfo{
    private: 
        u2 class_index;
        u2 name_and_type_index;

    public:
        CONSTANT_Fieldref_info();
};

#endif