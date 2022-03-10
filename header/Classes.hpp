#ifndef __Classes_HPP__
#define __Classes_HPP__

#include "Dados.hpp"

class Classes
{
public:
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
    Classes(u2 inner_class_info_index, u2 outer_class_info_index, u2 inner_name_index, u2 inner_class_access_flags);
};

#endif