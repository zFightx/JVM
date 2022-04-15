#ifndef __ReadFile_HPP__
#define __ReadFile_HPP__

#include <iostream>
#include <fstream>

#include "Dados.hpp"
#include "CpInfo.hpp"

using namespace std;

/**                                   
 * Representa as informações do Opcodes
 */
class ReadFile
{
public:

    /**                                   
    * @brief Lê um arquivo do tipo u1
    * @param file arquivo que vai ser lido
    */
    static u1 u1Read(ifstream &file);

    /**                                   
    * @brief Lê um arquivo do tipo u2
    * @param file arquivo que vai ser lido
    */
    static u2 u2Read(ifstream &file);

    /**                                   
    * @brief Lê um arquivo do tipo u4
    * @param file arquivo que vai ser lido
    */
    static u4 u4Read(ifstream &file);

    /**                                   
    * @brief Lê um arquivo do tipo u8
    * @param file arquivo que vai ser lido
    */
    static u8 u8Read(ifstream &file);

    /**                                   
    * @brief Lê um arquivo do tipo u1
    * @param bytes ponteiro de u1
    * @param length tamanho do arquivo
    */
    static string readByteString(u1 *bytes, u2 length);

    /**                                   
    * @brief Lê o pair string
    * @param index posição do arquivo
    * @param constant_pool é o constant_pool
    */
    static pair<string, vector<string>> readStringPair(int index, vector<CpInfo *> constant_pool);
    
    /**                                   
    * @brief Lê a string
    * @param index posição do arquivo
    * @param constant_pool é o constant_pool
    */
    static string readString(int index, vector<CpInfo *> constantPool);
    
    /**                                   
    * @brief Lê a string
    * @param index posição do arquivo
    * @param constant_pool é o constant_pool
    * @param vectorRet é um boolean para a referencia do arquivo
    */
    static vector<string> readString(int index, vector<CpInfo *> constantPool, bool vectorRet);

    /**                                   
    * @brief Pega o code short
    * @param code código do arquivo
    * @param i Valor do code
    */
    static int16_t getCodeShort(u1 *code, int i);

    /**                                   
    * @brief Pega o code short
    * @param code código do arquivo
    * @param i Valor do code
    */
    static uint16_t getCodeUShort(u1 *code, int i);

    /**                                   
    * @brief Pega o code short
    * @param code código do arquivo
    * @param i Valor do code
    */
    static int32_t getCodeInt(u1 *code, int i);
};

#endif