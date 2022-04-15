#include "../header/AttributeInfo.hpp"

AttributeInfo::AttributeInfo(){

}

AttributeInfo::AttributeInfo(u2 attribute_name_index, u4 attribute_length)
{
    this->attribute_name_index = attribute_name_index;
    this->attribute_length = attribute_length;
}

AttributeInfo::~AttributeInfo(){}