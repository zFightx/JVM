#ifndef __MethodAreaSection_hpp__
#define __MethodAreaSection_hpp__

#include <iostream>
#include <map>

#include "ClassFile.hpp"
#include "TypeValue.hpp"

/**                                    -------/CONFERIR TUDO/-------
 * Representa as informações do MethodAreaSection
 */
class MethodAreaSection
{
public:

    /**                                    
    * É o arquivo
    */
    ClassFile * class_file;

    /**                                    
    * Tabela de fields estáticos
    */
    map<string, Value> static_fields;

    /**                             
     * @brief Construtor padrão
     * @param cf O ponteiro para o class file
     */
    MethodAreaSection(ClassFile *cf);
};

#endif
