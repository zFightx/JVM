#include "../header/ObjectRef.hpp"
#include "../header/ReadFile.hpp"

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
            
            Value value;
            
            switch (field_descriptor[0]) {
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
                default:
                    value.type = 8;
                    value.data.object_value = NULL;
            }
            
            this->AddVariable(field_name, value);
        }
    }
}

void ObjectRef::AddVariable(string name, Value value){
    this->variables.insert({name, value});
}

void ObjectRef::ChangeVariable(string name, Value value){
    this->variables.at(name) = value;
}

Value ObjectRef::GetVariable(string name){
    return this->variables.at(name);
}