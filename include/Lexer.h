#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <string>
#include "Token.h"
#include "SymbolTable.h"

class Lexer {
private:
    std::ifstream sourceFile;
    int currentLine;
    int currentColumn;
    char currentChar;
    SymbolTable& symbolTable; // Referência para a tabela global

    void advance(); // Lê o próximo caractere
    void skipWhitespaceAndComments(); // Lida com espaços, \n, // e /* */

public:
    Lexer(const std::string& filename, SymbolTable& st);
    ~Lexer();

    // Função principal que o Parser chamará no futuro
    Token getNextToken(); 
};

#endif