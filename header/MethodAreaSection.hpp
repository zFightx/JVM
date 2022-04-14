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
    * Representa as informações do MethodAreaSection
    */
    ClassFile * class_file;
    map<string, Value> static_fields;

    /**                             
     * @brief Construtor padrão
     * @param cf O ponteiro para o class file
     */
    MethodAreaSection(ClassFile *cf);
    ~MethodAreaSection();
};

#endif
