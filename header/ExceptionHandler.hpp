#ifndef __ExceptionTable_HPP__
#define __ExceptionTable_HPP__

#include "Dados.hpp"

/**                                    -------/CONFERIR TUDO/-------
 * Representa as informações do ExceptionHandler
 */
class ExceptionHandler
{
public:

    /**
    * Manipulador ativo para o índice start_pc para code
    */
    u2 start_pc;

    /**
    * Manipulador ativo para o índice end_pc para code
    */
    u2 end_pc;

    /**
    * Índice para code indicando o bytecode inicial do manipulador
    */
    u2 handler_pc;

    /**
    * Se não nulo (cláusula catch de um comando try)
    */
    u2 catch_type;

    /**
     * @brief Construtor padrão.                 
     */
    ExceptionHandler();

    /**
     * @brief Sobrecarga do construtor com inicialização.
     * @param start_pc Manipulador ativo para o índice start_pc para code
     * @param end_pc Manipulador ativo para o índice end_pc para code
     * @param handler_pc Índice para code indicando o bytecode inicial do manipulador 
     * @param catch_type Se não nulo (cláusula catch de um comando try)               
     */
    ExceptionHandler(u2 start_pc, u2 end_pc, u2 handler_pc, u2 catch_type);
};

#endif