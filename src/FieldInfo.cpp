#include "../header/FieldInfo.hpp"
#include "../header/TypeValue.hpp"

FieldInfo::FieldInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count)
{
    this->access_flags = access_flags;
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes_count = attributes_count;
}

FieldInfo::~FieldInfo(){
    // delete this->attributes;
}

Value FieldInfo::FieldInit(string field_descriptor){

    Value value;

    if (field_descriptor == "Ljava/lang/String;"){
        value.type = 10;
        value.data.string_value = new string("");
    }
    else {
        switch (field_descriptor[0])
        {
        case 'B':
            value.type = 0;
            value.data.byte_value = 0;
            break;
        case 'C':
            value.type = 1;
            value.data.char_value = 0;
            break;
        case 'D':
            value.type = 2;
            value.data.double_value = 0;
            break;
        case 'F':
            value.type = 3;
            value.data.float_value = 0;
            break;
        case 'I':
            value.type = 4;
            value.data.int_value = 0;
            break;
        case 'J':
            value.type = 5;
            value.data.long_value = 0;
            break;
        case 'S':
            value.type = 6;
            value.data.short_value = 0;
            break;
        case 'Z':
            value.type = 7;
            value.data.char_value = false;
            break;
        case 'R':
            value.type = 9;
            value.data.return_address = 0;
            break; 
        default:
            value.type = 8;
            value.data.object_value = NULL;
        }
    }

    return value;
}