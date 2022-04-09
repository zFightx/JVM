#include "../header/MethodInfo.hpp"
#include "../header/Dados.hpp"
#include "../header/ReadFile.hpp"

MethodInfo::MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count)
{
    this->access_flags = access_flags;
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes_count = attributes_count;
}

MethodInfo::~MethodInfo(){
    // delete this->attributes;
}

void MethodInfo::getAttributeByName(string name, vector<CpInfo *> constant_pool, AttributeInfo &copy){
    for(int i = 0; i < this->attributes_count; i++){
        AttributeInfo attr = this->attributes[i];
        string attr_name = ReadFile::readString(attr.attribute_name_index, constant_pool);
        cout << attr_name << " " << name << endl;
        if(attr_name == name){
            cout << "ENCONTROU" << endl;
            copy = attr;
        }
    }
}
