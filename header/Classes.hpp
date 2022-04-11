#ifndef __Classes_HPP__
#define __Classes_HPP__

#include "Dados.hpp"

/**
 * Representa as classes da JVM. -----/CONFERIR/-----
 */
class Classes
{
public:
    /**
    * Informação interna da classe. 
    */
    u2 inner_class_info_index;

    /**
    * Informação externa da classe.
    */
    u2 outer_class_info_index;

    /**
    * Nome da classe. 
    */
    u2 inner_name_index;

    /**
    * Flags que a classe tem acesso. 
    */
    u2 inner_class_access_flags;

    /**
     * @brief Construtor padrão.
     */
    Classes();

    /**
     * @brief Sobrecarga do construtor com inicialização. 
     * @param inner_class_info_index Informação interna da classe.
     * @param outer_class_info_index Informação externa da classe.
     * @param inner_name_index Nome da classe. 
     * @param inner_class_access_flags Flags que a classe tem acesso.
     * @return A classe montada.
     */
    Classes(u2 inner_class_info_index, u2 outer_class_info_index, u2 inner_name_index, u2 inner_class_access_flags);
};

#endif