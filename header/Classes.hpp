#ifndef __Classes_HPP__
#define __Classes_HPP__

#include "Dados.hpp"

/**
 * Representa classes ou interfaces que não são membros de um pacote. 
 */
class Classes
{
public:
    /**
    * Índice válido para a tabela constant_pool
    */
    u2 inner_class_info_index;

    /**
    * Zero, se C não é um membro, ou índice válido da tabela constant_pool 
    */
    u2 outer_class_info_index;

    /**
    * Zero, se C é anônima, ou índice válido da tabela constant_pool
    */
    u2 inner_name_index;

    /**
    * Máscara de bits especificando permissões de acesso e propriedades da classe ou
    * interface C declaradas no fonte.
    */
    u2 inner_class_access_flags;

    /**                            
     * @brief Construtor padrão.  
     */
    Classes();

    /**                             
     * @brief Sobrecarga do construtor com inicialização. 
     * @param inner_class_info_index Índice válido para a tabela constant_pool
     * @param outer_class_info_index Zero, se C não é um membro, ou índice válido da tabela constant_pool
     * @param inner_name_index Zero, se C é anônima, ou índice válido da tabela constant_pool
     * @param inner_class_access_flags Máscara de bits especificando permissões de acesso e propriedades da classe ou interface C declaradas no fonte 
     */
    Classes(u2 inner_class_info_index, u2 outer_class_info_index, u2 inner_name_index, u2 inner_class_access_flags);
};

#endif