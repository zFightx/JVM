#ifndef __FieldInfo_HPP__
#define __FieldInfo_HPP__

#include <vector>
#include "Dados.hpp"
#include "AttributeInfo.hpp"
#include "TypeValue.hpp"

using namespace std;

struct Value;

/**                                    
 * Representa as informações do FieldInfo
 */
class FieldInfo
{
public:

    /**
    * Máscara de hexadecimais especificando permissões de acesso e propriedades do campo
    */
    u2 access_flags;

    /**
    * Representa um nome simples de field
    */
    u2 name_index;

    /**
    * Representa um descritor de campo válido.
    */
    u2 descriptor_index;

    /**
    * Número de atributos do campo
    */
    u2 attributes_count;

    /**
    * Tabela com os atributos
    */
    AttributeInfo * attributes;

    /**
     * @brief Construtor padrão.                
     * @param access_flags Máscara de hexadecimais especificando permissões de acesso e propriedades do campo
     * @param name_index Representa um nome simples de field
     * @param descriptor_index Representa um descritor de campo válido
     * @param attributes_count Número de atributos do campo
     */
    FieldInfo(u2 access_flags, u2 name_index, u2 descriptor_index, u2 attributes_count);

    /**
     * @brief Destrutor padrão.
     */
    ~FieldInfo();

    /**
     * @brief Inicializa o field.                
     * @param field_descriptor descrição do field a ser inicializado
     * @return O field inicializado
     */
    static Value FieldInit(string field_descriptor);
};

#endif