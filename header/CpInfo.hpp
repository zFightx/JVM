#ifndef __CpInfo_HPP__
#define __CpInfo_HPP__

#include "Dados.hpp"
#include "TypeConstant.hpp"

/**                                   
 * Representa as informações do CPInfo 
 */
class CpInfo
{
public:

    /**
    * O byte de tag define o tipo da informação   
    */
    u1 tag;

    /**
    * Union de tipos do atributo.
    */
    union info
    {

        /**
        * Representa uma Classe ou Interface   
        */
        CONSTANT_Class_info Class;                           //! 7

        /**
        * Representa um field    
        */
        CONSTANT_Fieldref_info Fieldref;                     //! 9

        /**
        * Representa um método    
        */
        CONSTANT_Methodref_info Methodref;                   //! 10

        /**
        * Representa uma interface ou método   
        */
        CONSTANT_InterfaceMethodref_info InterfaceMethodref; //! 11

        /**
        * Representa um field ou método sem indicar classe ou interface a que pertence    
        */
        CONSTANT_NameAndType_info NameAndType;               //! 12

        /**
        * Representa valores strings constantes, inclusive Unicode    
        */
        CONSTANT_Utf8_info Utf8;                             //! 1

        /**
        * Representa objetos constantes do tipo String  
        */
        CONSTANT_String_info String;                         //! 8

        /**
        * Representa uma constante inteira de 4 bytes    
        */
        CONSTANT_Integer_info Integer;                       //! 3

        /**
        * Representa uma constante de ponto flutuante de 4 bytes   
        */
        CONSTANT_Float_info Float;                           //! 4

        /**
        * Representa uma constante inteira de 8 bytes, armazenados em big-endian ordem  
        */
        CONSTANT_Long_info Long;                             //! 5

        /**
        * Representa constante de ponto flutuante de 8 bytes, armazenados em big-endian ordem, 
        no formato de ponto flutuante de dupla precisão IEEE 754
        */
        CONSTANT_Double_info Double;                         //! 6
    } info;

    /**
     * @brief Construtor padrão.                
     * @param tag Tag do CPInfo 
     */
    CpInfo(u1 tag);

    /**
     * @brief Destrutor padrão.
     */
    ~CpInfo();
};

#endif