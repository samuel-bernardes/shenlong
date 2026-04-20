#include <iostream>
#include "Lexer.h"
#include "SymbolTable.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./compilador <arquivo_fonte>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    
    SymbolTable symbolTable;
    
    Lexer lexer(filename, symbolTable);

    Token token;
    
    std::cout << "TOKENS: " << std::endl;
    do {
        token = lexer.getNextToken();
        std::cout << "Token: " << static_cast<int>(token.type) 
                  << " | Lexema: '" << token.lexeme << "'" 
                  << " | Linha: " << token.line 
                  << " | Coluna: " << token.column << std::endl;
                  
        // Se houver erro léxico, você pode optar por parar ou reportar e continuar
        if (token.type == TokenType::ERROR) {
    std::cout << "ERRO LEXICO: lexema invalido '"
              << token.lexeme
              << "' na linha " << token.line
              << ", coluna " << token.column
              << std::endl;
}
        
    } while (token.type != TokenType::END_OF_FILE);

    std::cout << "\nTABELA DE SIMBOLOS: " << std::endl;
    symbolTable.printTable();

    return 0;
}