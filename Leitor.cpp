
#include <iostream>
#include <iomanip>
#include <fstream>

#include "header/ClassFile.hpp"
#include "header/Dados.hpp"
#include "header/ReadFile.hpp"
#include "header/Runtime.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    string file = "";
    cout << "Por favor, digite o nome do arquivo: ";
    cin >> file;
    // ClassFile *class_file = new ClassFile(file);

    // class_file->MenuClassFile();

    // delete class_file;

    Runtime *runtime = new Runtime(file);

    map<string, MethodAreaSection*>::iterator it;
    
    for (it = runtime->method_area.begin(); it != runtime->method_area.end(); it++)
    {
        cout << "printnaod" << " " << it->second->class_file->this_class << endl;

        map<string, Value>::iterator it2;
        for (it2 = it->second->static_fields.begin(); it2 != it->second->static_fields.end(); it2++)
        {
            cout << "type : " << (int) it2->second.type << endl;
            if(it2->second.type == 8){
                cout << it2->first << " : " << it2->second.data.object_value << endl;
            }
        }
    }

    cout << "aqui" << endl;
    delete runtime;

    return 0;
}