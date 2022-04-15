#ifndef __Link_HPP__
#define __Link_HPP__

#include <iostream>
#include <map>

#include "Dados.hpp"
#include "ClassFile.hpp"
#include "MethodAreaSection.hpp"
#include "Runtime.hpp"

using namespace std;

/**                                   
 * Representa as informações do ClassLoaderSubsystem. 
 */
class ClassLoaderSubsystem
{
public:
    
    /**                             
     * @brief Faz a verificação da Classe. 
     * @param cafeBabe Assinatura do arquivo .class
     * @param minorVersion Indicam a versão do formato na forma M.m (representa o m)
     * @param majorVersion Indicam a versão do formato na forma M.m (representa o M)
     * @param sourceFileFontName Nome da fonte da classe
     * @param fontName Nome da classe
     */
    static void Verify(u4 cafeBabe, u2 minorVersion, u2 majorVersion, string sourceFileFontName, string fontName);
    
    /**                             
     * @brief Prepara a Classe. 
     * @param cf Um ponteiro para um ClassFile
     */
    static void Prepare(ClassFile *cf);

    /**                             
     * @brief Resolve a Classe. 
     * @param class_name Nome da classe
     * @param runtime Tempo de execução
     */
    static void Resolve(string class_name, Runtime * runtime);

    /**                             
     * @brief Inicializa a Classe. 
     * @param class_file Ponteiro para o ClassFile
     * @param runtime Tempo de execução
     */
    static void Initialize(ClassFile *class_file, Runtime *runtime);

    /**                             
     * @brief Inicializa a Classe. 
     * @param index
     * @param constant_pool
     */
    static string GetStringConstantPool(u2 index, vector<CpInfo *> constant_pool);
};

#endif