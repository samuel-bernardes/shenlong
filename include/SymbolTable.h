#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include "Token.h"

class SymbolTable {
private:
    std::unordered_map<std::string, TokenType> table;

public:
    SymbolTable(); // Construtor deve pré-carregar as palavras reservadas
    
    // Instala um novo identificador
    void insert(const std::string& lexeme, TokenType type);
    
    // Verifica se existe e retorna o tipo (útil para saber se é palavra reservada ou ID)
    TokenType lookup(const std::string& lexeme);
    
    // Método para imprimir a tabela no relatório da Etapa 1
    void printTable() const; 
};

#endif