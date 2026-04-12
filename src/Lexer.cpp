#include "../include/Lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& filename, SymbolTable& st) : symbolTable(st) {
    sourceFile.open(filename);
    if (!sourceFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << filename << std::endl;
        exit(1);
    }
    
    currentLine = 1;
    currentColumn = 0;
    advance(); // Lê o primeiro caractere para iniciar o motor
}

Lexer::~Lexer() {
    if (sourceFile.is_open()) {
        sourceFile.close();
    }
}

// Avança um caractere no arquivo e controla linha/coluna
void Lexer::advance() {
    currentChar = sourceFile.get();
    currentColumn++;
    if (currentChar == '\n') {
        currentLine++;
        currentColumn = 0;
    }
}

// Filtro de ruídos: espaços, tabs, quebras de linha e comentários
void Lexer::skipWhitespaceAndComments() {
    while (currentChar != EOF) {
        if (isspace(currentChar)) {
            advance();
        } 
        // Comentário de uma linha //
        else if (currentChar == '/') {
            char nextChar = sourceFile.peek(); // Olha o próximo sem avançar de fato
            if (nextChar == '/') {
                advance(); advance(); // Consome as duas barras '//'
                while (currentChar != '\n' && currentChar != EOF) {
                    advance();
                }
            } 
            // Comentário de múltiplas linhas /* ... */
            else if (nextChar == '*') {
                advance(); advance(); // Consome '/*'
                while (currentChar != EOF) {
                    if (currentChar == '*') {
                        advance();
                        if (currentChar == '/') {
                            advance(); // Consome o '/' final
                            break;
                        }
                    } else {
                        advance();
                    }
                }
            } else {
                break; // É apenas uma barra de divisão '/', o Lexer vai tratar depois
            }
        } else {
            break; // Não é espaço nem comentário, sai do loop
        }
    }
}

// A Máquina de Estados principal
Token Lexer::getNextToken() {
    skipWhitespaceAndComments();

    Token token;
    token.line = currentLine;
    token.column = currentColumn;

    // 1. Fim de Arquivo
    if (currentChar == EOF) {
        token.type = TokenType::END_OF_FILE;
        token.lexeme = "EOF";
        return token;
    }

    // 2. Identificadores e Palavras Reservadas (Começa com letra)
    if (isalpha(currentChar)) {
        std::string lexeme = "";
        while (isalnum(currentChar)) { // Aceita letras ou números
            lexeme += currentChar;
            advance();
        }
        
        token.lexeme = lexeme;
        token.type = symbolTable.lookup(lexeme);
        
        // Se for um ID novo, instala na tabela
        if (token.type == TokenType::IDENTIFIER) {
            symbolTable.insert(lexeme, TokenType::IDENTIFIER);
        }
        return token;
    }

    // 3. Constantes Inteiras e Reais (Começa com número)
    if (isdigit(currentChar)) {
        std::string numStr = "";
        while (isdigit(currentChar)) {
            numStr += currentChar;
            advance();
        }
        
        // Verifica se é um número real (tem ponto e mais números)
        if (currentChar == '.') {
            numStr += currentChar;
            advance();
            while (isdigit(currentChar)) {
                numStr += currentChar;
                advance();
            }
            token.type = TokenType::REAL_CONST;
        } else {
            token.type = TokenType::INTEGER_CONST;
        }
        token.lexeme = numStr;
        return token;
    }

    // 4. Strings Literais (Começa com aspas duplas)
    if (currentChar == '"') {
        std::string literalStr = "\"";
        advance(); // Consome a primeira aspa
        
        while (currentChar != '"' && currentChar != EOF && currentChar != '\n') {
            literalStr += currentChar;
            advance();
        }
        
        if (currentChar == '"') {
            literalStr += currentChar;
            advance(); // Consome a aspa final
            token.type = TokenType::LITERAL;
        } else {
            token.type = TokenType::ERROR; // Fechamento de aspas ausente
        }
        token.lexeme = literalStr;
        return token;
    }

    // 5. Operadores e Pontuação (O autômato de caracteres únicos/duplos)
    token.lexeme = std::string(1, currentChar);
    
    switch (currentChar) {
        case '+':
            token.type = TokenType::PLUS;
            advance();
            break;
        case '-':
            token.type = TokenType::MINUS;
            advance();
            break;
        case ';':
            token.type = TokenType::SEMICOLON;
            advance();
            break;
        case '(':
            token.type = TokenType::LPAREN;
            advance();
            break;
        case ')':
            token.type = TokenType::RPAREN;
            advance();
            break;
        case '{':
            token.type = TokenType::LBRACE;
            advance();
            break;
        case '}':
            token.type = TokenType::RBRACE;
            advance();
            break;
            
        // Operadores Compostos (Lookahead)
        case ':':
            advance();
            if (currentChar == '=') {
                token.type = TokenType::ASSIGN;
                token.lexeme = ":=";
                advance();
            } else {
                token.type = TokenType::ERROR; // ':' sozinho não existe na linguagem
            }
            break;
            
        case '>':
            advance();
            if (currentChar == '=') {
                token.type = TokenType::GREATER_EQ;
                token.lexeme = ">=";
                advance();
            } else {
                token.type = TokenType::GREATER;
            }
            break;

        // TODO: Adicionar os cases para '<' (pode virar <= ou <>), '=', '*', '/', '%', ',', '.'
            
        default:
            token.type = TokenType::ERROR;
            advance();
            break;
    }

    return token;
}