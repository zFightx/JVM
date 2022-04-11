#ifndef __AttributeInfo_HPP__
#define __AttributeInfo_HPP__

#include <vector>

#include "Dados.hpp"
#include "TypeAttribute.hpp"

/**
 * Representa os atributos relacionados ao ClassFile.
 */
class AttributeInfo
{
public:
    /**
    * O nome do atributo.
    */
    u2 attribute_name_index;

    /**
    * O tamanho do atributo.
    */
    u4 attribute_length;

    /**
    * Union de tipos do atributo.
    */
    union Info
    {
        ConstantValue_attribute ConstantValue;
        Code_attribute Code;
        Exceptions_attribute Exceptions;
        InnerClasses_attribute InnerClasses;
        Synthetic_attribute Synthetic;
        SourceFile_attribute SourceFile;
        
    } info;
    
    /**
     * @brief Construtor padrão.
     */
    AttributeInfo();

    /**
     * @brief Destrutor padrão.
     */
    ~AttributeInfo();

    /**
     * @brief Sobrecarga do construtor com inicialização.
     * @param attribute_name_index O nome do atributo.
     * @param attribute_length O tamanho do atributo.
     */
    AttributeInfo(u2 attribute_name_index, u4 attribute_length);
};

#endif