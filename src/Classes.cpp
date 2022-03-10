#include "../header/Classes.hpp"

Classes::Classes(){

}

Classes::Classes(u2 inner_class_info_index, u2 outer_class_info_index, u2 inner_name_index, u2 inner_class_access_flags){
    this->inner_class_info_index = inner_class_info_index;
    this->outer_class_info_index = outer_class_info_index;
    this->inner_name_index = inner_name_index;
    this->inner_class_access_flags = inner_class_access_flags;
}