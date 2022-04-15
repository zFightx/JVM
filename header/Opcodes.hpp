#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include <iostream>
#include <vector>
#include <map>
#include "Dados.hpp"
#include "CpInfo.hpp"

using namespace std;

/**                                    -------/CONFERIR TUDO/-------
 * Representa as informações do Opcodes
 */
class Opcodes
{
public:

    /**
    * Tabela de opcodes
    */
    static map<int, pair<string, int>> opcodes;

    /**                             
     * @brief Construtor padrão
     */
    static void CreateOpcodes();

    /**                             
     * @brief Sobrecarga do construtor com inicialização. 
     * @param code código 
     * @param size Tamanho do código
     * @param constantPool Pool de constantes
     */
    static void PrintOpcodes(u1 *code, int size, vector<CpInfo *> constantPool);
};

#endif