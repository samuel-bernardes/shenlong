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

// Retorna o nome legível do tipo de token
inline std::string tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::CLASS:        return "CLASS";
        case TokenType::INT:          return "INT";
        case TokenType::STRING:       return "STRING";
        case TokenType::FLOAT:        return "FLOAT";
        case TokenType::IF:           return "IF";
        case TokenType::ELSE:         return "ELSE";
        case TokenType::DO:           return "DO";
        case TokenType::WHILE:        return "WHILE";
        case TokenType::REPEAT:       return "REPEAT";
        case TokenType::UNTIL:        return "UNTIL";
        case TokenType::READ:         return "READ";
        case TokenType::WRITE:        return "WRITE";
        case TokenType::IDENTIFIER:   return "IDENTIFIER";
        case TokenType::INTEGER_CONST:return "INTEGER_CONST";
        case TokenType::REAL_CONST:   return "REAL_CONST";
        case TokenType::LITERAL:      return "LITERAL";
        case TokenType::ASSIGN:       return "ASSIGN";
        case TokenType::PLUS:         return "PLUS";
        case TokenType::MINUS:        return "MINUS";
        case TokenType::MULT:         return "MULT";
        case TokenType::DIV:          return "DIV";
        case TokenType::MOD:          return "MOD";
        case TokenType::AND:          return "AND";
        case TokenType::OR:           return "OR";
        case TokenType::NOT:          return "NOT";
        case TokenType::GREATER:      return "GREATER";
        case TokenType::LESS:         return "LESS";
        case TokenType::GREATER_EQ:   return "GREATER_EQ";
        case TokenType::LESS_EQ:      return "LESS_EQ";
        case TokenType::EQUAL:        return "EQUAL";
        case TokenType::NOT_EQUAL:    return "NOT_EQUAL";
        case TokenType::SEMICOLON:    return "SEMICOLON";
        case TokenType::COMMA:        return "COMMA";
        case TokenType::DOT:          return "DOT";
        case TokenType::LPAREN:       return "LPAREN";
        case TokenType::RPAREN:       return "RPAREN";
        case TokenType::LBRACE:       return "LBRACE";
        case TokenType::RBRACE:       return "RBRACE";
        case TokenType::END_OF_FILE:  return "END_OF_FILE";
        case TokenType::ERROR:        return "ERROR";
        default:                      return "UNKNOWN";
    }
}

// Estrutura do Token que será retornada pelo Lexer
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

#endif