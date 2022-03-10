﻿#include "../header/MethodInfo.hpp"
#include "../header/Dados.hpp"

MethodInfo::MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count)
{
    this->access_flags = access_flags;
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes_count = attributes_count;
}