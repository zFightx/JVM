#ifndef __Runtime_HPP__
#define __Runtime_HPP__

#include <iostream>
#include <map>

#include "MethodAreaSection.hpp"
#include "Frame.hpp"

using namespace std;

/**                                   
 * Representa as informações do Runtime
 */
class Runtime
{
private:
public:

    /**                                   
    * É a clase principal
    */
    static string main_class_name;

    /**                                   
    * É a clase principal
    */
    static vector<Value> args;

    /**                                   
    * É o method area
    */
    map<string, MethodAreaSection *> method_area;

    /**                                   
    * É a pilha
    */
    vector<Frame *> stack;
    
    /**                                   
    * @brief Construtor padrão
    * @param class_name nome da classe
    * @param args argumentos da classe
    */
    Runtime(string class_name, vector<Value> args = vector<Value> ());

    /**                                   
    * @brief Destrutor padrão
    */
    ~Runtime();

    /**                                   
    * @brief Dá push em um frame
    * @param fr Frame que vai receber o push
    */
    void PushFrame(Frame *fr);

    /**                                   
    * @brief Deleta o frame
    */
    void PopFrame();

    /**                                   
    * @brief inicializa o frame
    * @param method_name Nome do metodo
    * @param descriptor Descrição do Frame
    * @param class_file Arquivo
    * @param args São os argumentos
    */
    void InitializeFrame(string method_name, string descriptor, ClassFile *class_file, vector<Value> args = vector<Value>());
    
    /**                                   
    * @brief Pega a frame atual
    * @return Retorna o frame atual
    */
    Frame * GetCurrentFrame();

    /**                                   
    * @brief Adiciona uma área de método
    * @param class_name nome da classe
    */
    void AddMethodArea(string class_name);
};

#endif