#ifndef __MethodInfo_HPP__
#define __MethodInfo_HPP__

#include <vector>
#include <iostream>

#include "Dados.hpp"
#include "AttributeInfo.hpp"
#include "CpInfo.hpp"

using namespace std;

/**                                    -------/CONFERIR TUDO/-------
 * Representa as informações do MethodInfo
 */
class MethodInfo
{
private:
public:

    /**
    * Máscara de hexadecimais especificando permissões de acesso e propriedades do método
    */
    u2 access_flags;

    /**
    * É um índice válido para a tabela constant_pool representando um nome especial de método 
    */
    u2 name_index;

    /**
    * É um índice válido para a tabela constant_pool representando um descritor de método válido
    */
    u2 descriptor_index;

    /**
    * Número de atributos do Método
    */
    u2 attributes_count;

    /**
    * Usados nas estruturas ClassFile, field_info, method_info e code_attribute
    */
    AttributeInfo *attributes;

    /**                             
     * @brief Construtor padrão
     * @param access_flags Máscara de hexadecimais especificando permissões de acesso e propriedades do método
     * @param name_index É um índice válido para a tabela constant_pool representando um nome especial de método 
     * @param descriptor_index É um índice válido para a tabela constant_pool representando um descritor de método válido
     * @param attributes_count Número de atributos do Método
     */
    MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count);

    /**                             
     * @brief Destrutor padrão
     */
    ~MethodInfo();

    /**                             
     * @brief Acha o atributo pelo nome
     * @param name Nome do atributo 
     * @param constant_pool Vetor com os constant pool
     * @param copy Uma cópia do atributo
     */
    void getAttributeByName(string name, vector<CpInfo*> constant_pool, AttributeInfo &copy);
    
};
#endif