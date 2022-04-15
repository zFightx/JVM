#ifndef __FRAME_H__
#define __FRAME_H__

#include <iostream>
#include <vector>
#include <map>

#include "CpInfo.hpp"
#include "TypeValue.hpp"

/**                               
 * Representa as informações do Frame
 */
class Frame
{
private:
    
public:

    /**
    * Tabela com as variáveis locais
    */
    map<int, Value> local_variables;

    /**
    * Pilha de operandos
    */
    vector<Value> operand_stack;

    /**
    * Tabela de estruturas representando string, nomes de classes ou interfaces, nomes de campos, ...
    */
    vector<CpInfo*> constant_pool;

    /**
    * Atributo de tamanho variável, somente um atributo code é possível por método
    */
    Code_attribute code;

    /**
    * Índice para o array code correspondendo ao código
    */
    int pc;

    /**
     * @brief Construtor padrão.
     */
    Frame();

    /**                             
     * @brief Sobrecarga do construtor com inicialização. 
     * @param constant_pool Tabela de estruturas representando string, nomes de classes ou interfaces, nomes de campos, ...
     * @param code Atributo de tamanho variável, somente um atributo code é possível por método
     */
    Frame(vector<CpInfo*> constant_pool, Code_attribute code);

    /**
     * @brief Destrutor padrão.
     */
    ~Frame();

    /**                             
     * @brief Coloca um operando na pilha 
     * @param Value Operando a ser colocado na pilha
     */
    void PushOperandStack(Value);

    /**                             
     * @brief Retira um operando da pilha 
     * @return O operando que foi retirado da pilha
     */
    Value PopOperandStack();

    /**                             
     * @brief Adiciona uma variável na pilha 
     * @param Value Variável a ser adicionada na pilha
     */
    void AddLocalVariable(Value);

    /**                             
     * @brief Retira uma variavel 
     * @return O valor da variavel que foi retirada
     */
    Value GetLocalVariable(int index);

    /**                             
     * @brief Modifica uma variável na pilha 
     * @param index Posição da variável a ser modificada
     * @param Value Novo valor da variavel
     */
    void ChangeLocalVariable(int index, Value);

    /**                             
     * @brief Adiciona um operando na pilha 
     * @param Value Valor do operando
     */
    void AddOperandStack(Value);

    /**                             
     * @brief Redefine o constant pool
     * @param cp Novo valor do constant pool
     */
    void SetContantPool(vector<CpInfo*> &cp);
};

#endif