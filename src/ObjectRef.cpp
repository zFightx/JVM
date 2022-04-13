#include "../header/ObjectRef.hpp"
#include "../header/ReadFile.hpp"
#include "../header/FieldInfo.hpp"

ObjectRef::ObjectRef(ClassFile *class_file){
    this->class_file = class_file;
    vector<FieldInfo *> fields = class_file->fields;
    u2 fields_count = class_file->fields_count;

    for (int i = 0; i < fields_count; i++) {
        FieldInfo *field = fields[i];

         // verifica se é não estática e não final
        if (field->access_flags != 0x0008 && field->access_flags != 0x0010) {
            string field_name = ReadFile::readString(field->name_index, class_file->constant_pool);
            string field_descriptor = ReadFile::readString(field->descriptor_index, class_file->constant_pool);
            
            Value value = FieldInfo::FieldInit(field_descriptor);
            
            
            this->AddVariable(field_name, value);
        }
    }
}

void ObjectRef::AddVariable(string name, Value value){
    this->variables[name] = value;
}

void ObjectRef::ChangeVariable(string name, Value value){
    this->variables[name] = value;
}

Value ObjectRef::GetVariable(string name){
    return this->variables[name];
}