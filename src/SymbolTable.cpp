#include "../include/SymbolTable.h"
#include <iostream>

// Construtor: Pré-carrega as palavras reservadas da linguagem
SymbolTable::SymbolTable() {
    table["class"] = TokenType::CLASS;
    table["int"] = TokenType::INT;
    table["string"] = TokenType::STRING;
    table["float"] = TokenType::FLOAT;
    table["if"] = TokenType::IF;
    table["else"] = TokenType::ELSE;
    table["do"] = TokenType::DO;
    table["while"] = TokenType::WHILE;
    table["repeat"] = TokenType::REPEAT;
    table["until"] = TokenType::UNTIL;
    table["read"] = TokenType::READ;
    table["write"] = TokenType::WRITE;
    
    table["and"] = TokenType::AND;
    table["or"] = TokenType::OR;
    table["not"] = TokenType::NOT;
}

// Retorna o tipo se existir. Se não existir, avisa que é um ID genérico.
TokenType SymbolTable::lookup(const std::string& lexeme) {
    auto it = table.find(lexeme);
    if (it != table.end()) {
        return it->second; // Retorna a palavra reservada ou ID já cadastrado
    }
    return TokenType::IDENTIFIER; // Se não achou, é um identificador novo
}

// Instala um novo identificador na tabela
void SymbolTable::insert(const std::string& lexeme, TokenType type) {
    table[lexeme] = type;
}

// Imprime a tabela (exigência do relatório da Etapa 1)
void SymbolTable::printTable() const {
    std::cout << "LEXEMA | TIPO\n";
    for (const auto& pair : table) {
        std::cout << pair.first << " | " << static_cast<int>(pair.second) << "\n";
    }
}