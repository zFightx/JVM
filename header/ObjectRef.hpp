#ifndef __ObjectRef_HPP__
#define __ObjectRef_HPP__

#include <string>
#include <map>

#include "TypeValue.hpp"
#include "ClassFile.hpp"

using namespace std;

class ClassFile;
struct Value;

/**                                    -------/CONFERIR TUDO/-------
 * Representa as informações do ObjectRef
 */
class ObjectRef
{
public:

    /**
    * Tabela de variáveis
    */
    map<string, Value> variables;

    /**
    * É o arquivo
    */
    ClassFile *class_file;

    /**                             
     * @brief Construtor padrão
     * @param class_file Arquivo que foi lido
     */
    ObjectRef(ClassFile *class_file);

    /**                             
     * @brief Destrutor padrão
     */
    ~ObjectRef();

    /**                             
     * @brief Adiciona a variável
     * @param string Nome da variável
     * @param Value Valor da variável
     */
    void AddVariable(string, Value);

    /**                             
     * @brief Muda a variável
     * @param string Nome da variável
     * @param Value Novo valor da variável
     */
    void ChangeVariable(string, Value);

    /**                             
     * @brief Pega uma variável
     * @param string Nome da variável
     * @return O valor da variável
     */
    Value GetVariable(string);
};

#endif