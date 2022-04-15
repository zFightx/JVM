#include "../header/CpInfo.hpp"

CpInfo::CpInfo(u1 tag){
    this->tag = tag;    
}

CpInfo::~CpInfo(){
    if(this->tag == 1){
        delete [] this->info.Utf8.bytes;
    }
}