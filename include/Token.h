#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Enum com todos os tipos de tokens baseados na gramática
enum class TokenType {
    // Palavras Reservadas
    CLASS, INT, STRING, FLOAT, IF, ELSE, DO, WHILE, REPEAT, UNTIL, READ, WRITE,
    
    // Identificadores e Constantes
    IDENTIFIER, INTEGER_CONST, REAL_CONST, LITERAL,
    
    // Operadores e Pontuação
    ASSIGN,         // :=
    PLUS, MINUS,    // +, -
    MULT, DIV, MOD, // *, /, %
    AND, OR, NOT,   // and, or, not
    GREATER, LESS,  // >, <
    GREATER_EQ,     // >=
    LESS_EQ,        // <=
    EQUAL,          // =
    NOT_EQUAL,      // <>
    
    SEMICOLON,      // ;
    COMMA,          // ,
    DOT,            // .
    LPAREN, RPAREN, // ( )
    LBRACE, RBRACE, // { }
    
    // Fim de Arquivo e Erros
    END_OF_FILE,
    ERROR
};

// Estrutura do Token que será retornada pelo Lexer
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

#endif