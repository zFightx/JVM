#ifndef __ClassFile_HPP__
#define __ClassFile_HPP__

#include <iostream>
#include <vector>

#include "Dados.hpp"
#include "CpInfo.hpp"
#include "FieldInfo.hpp"
#include "MethodInfo.hpp"
#include "AttributeInfo.hpp"

using namespace std;


class FieldInfo;

/**                                    
 * Representa as informações do ClassFile. 
 */
class ClassFile
{

public:

    /**
    * Assinatura do arquivo .class 
    */
    u4 magic;

    /**
    * Indicam a minor_version  
    */
    u2 minor_version;

    /**
    * Indicam a versão do formato na forma M.m
    */
    u2 major_version;
    
    /**
    * Número de entradas na tabela constant_pool + 1 
    */
    u2 constant_pool_count;
    
    /**
    * Tabela de estruturas representando string, nomes de classes ou interfaces, nomes de campos, ...
    * referidos dentro de estruturas do ClassFile e suas subestruturas. 
    */
    vector<CpInfo *> constant_pool;
    
    /**
    * Máscara de bits que especifica permissões de acesso e propriedades da classe ou interface
    */
    u2 access_flags;
    
    /**
    * Representa a classe ou interface  
    */
    u2 this_class;
    
    /**
    * Representa a super classe direta (classe mãe) da classe definida nesse arquivo
    * Se for 0 essa classe estende a classe Object 
    */
    u2 super_class;
    
    /**
    * Número de entradas no array interfaces[ ]. 
    */
    u2 interfaces_count;
    
    /**
    * Representa uma interface que é uma superinterface direta da classe 
    */
    vector<u2> interfaces;
    
    /**
    * Número de estruturas FieldInfo na tabela fields [ ]
    */
    u2 fields_count;
    
    /**
    * A Tabela inclui apenas os campos declarados na classe ou interface.
    * Não inclui campos herdados das superclasses ou superinterfaces.
    */
    vector<FieldInfo *> fields;
    
    /**
    * Número de estruturas MethodInfo na tabela methods[ ]
    */
    u2 methods_count;
    
    /**
    * Tabela com todos os tipos de método (declarados pela classe ou interface, de instância, estáticos, 
    * iniciação de instância, e qualquer método de iniciação de classe ou interface)
    * Essa tabela não inclui itens representando métodos herdados de superclasses ou superinterfaces
    */
    vector<MethodInfo *> methods;
    
    /**
    * Número de estruturas AttributesInfo na tabela attributes[ ] 
    */
    u2 attributes_count;
    
    /**
    * Tabela com os atributos  
    */
    AttributeInfo *attributes;

    /**
     * @brief Construtor padrão.                
     * @param file String que representa o arquivo da classe 
     */
    ClassFile(string file);

    /**
     * @brief Destrutor padrão.
     */
    ~ClassFile();

    /**
     * @brief Cria o ConstantPool da classe        
     * @param file Arquivo de leitura aberto da classe
     */
    void CreateConstantPool(ifstream &file);

    /**
     * @brief Cria as interfaces da classe        
     * @param file Arquivo de leitura aberto da classe
     */
    void CreateInterfaces(ifstream &file);

    /**
     * @brief Cria o FieldInfo da classe         
     * @param file Arquivo de leitura aberto da classe
     */
    void CreateFieldInfo(ifstream &file);

    /**
     * @brief Cria os métodos da classe        
     * @param file Arquivo de leitura aberto da classe
     */
    void CreateMethodInfo(ifstream &file);

    /**
     * @brief Cria o AttributeInfo da classe         
     * @param file String com as informações da classe que vão ser criadas
     * @param attributes_count Número de estruturas AttributesInfo na tabela attributes []
     * @return Retorna o AttributeInfo criado
     */
    AttributeInfo *CreateAttributeInfo(ifstream &file, u2 attributes_count);

    /**
     * @brief Deleta uma lista recursivamente de atributos         
     * @param attributes Ponteiro do vetor de attributes
     * @param attributes_count Número de estruturas AttributesInfo na tabela attributes []
     */
    void DeleteAttributes(AttributeInfo *attributes, u2 attributes_count);

    /**                                      
     * @brief Invoca todas as funções de printar do ClassFile
     */
    void MenuClassFile();

    /**                                    
     * @brief Printa o GeneralInformation
     */
    void GeneralInformation();

    /**                                      
     * @brief Printa o MenuConstantPool
     */
    void MenuConstantPool();

    /**                                      
     * @brief Printa o MenuInterfaces
     */
    void MenuInterfaces();

    /**                                      
     * @brief Printa o MenuFields
     */
    void MenuFields();

    /**                                      
     * @brief Printa o MenuAttributes
     */
    void MenuAttributes();

    /**                                      
     * @brief Printa o MenuMethodInfo
     */
    void MenuMethodInfo();

    /**
     * @brief Printa o atributo         
     * @param attributes Atributo a ser mostrado
     * @param attributes_count Número de estruturas AttributesInfo na tabela attributes []
     */
    void PrintAttributes(AttributeInfo *attributes, u2 attributes_count);

    /**
     * @brief Printa o atributo        
     * @param access_flags Máscara de bits que especifica permissões de acesso e propriedades da classe ou interface
     * @param flagType Tipo da flag
     */
    void PrintAccessFlags(u2 access_flags, int flagType);

    /**
     * @brief Ler a string        -----/CONFERIR/----- 
     * @param index É um inteiro de onde está a string
     * @return Retorna a string que estava no index passado
     */
    string readString(int index);

    /**
     * @brief Ele acha o método pelo nome        
     * @param name É o nome do método
     * @return Retorna o método
     */
    MethodInfo* getMethodByName(string name);

    /**
     * @brief Ele acha o método pelo nome e descrição      
     * @param name É o nome do método
     * @param descriptor É uma string com a descrição do método
     * @return Retorna o método
     */
    MethodInfo* getMethodByNameAndDescriptor(string name, string descriptor);
};

#endif