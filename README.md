# Shenlong

Shenlong é um compilador educacional desenvolvido em C++, inspirado nos princípios clássicos de construção de compiladores e nos dragões icônicos dos livros de teoria de compiladores.

O projeto implementa o pipeline completo de compilação — análise léxica, análise sintática, análise semântica e geração de código intermediário — para uma linguagem de programação didática.

Desenvolvido como trabalho prático da disciplina de Compiladores (CEFET-MG, Engenharia de Computação — Prof.ª Kecia Marques, 2026/1).

## Status do desenvolvimento

O trabalho é dividido em três etapas:

| Etapa | Descrição | Status |
|-------|-----------|--------|
| 1 | Analisador Léxico e Tabela de Símbolos | ✅ Concluído |
| 2 | Analisador Sintático | 🔜 Em desenvolvimento |
| 3 | Analisador Semântico e Gerador de Código | ⏳ Pendente |

## A Linguagem

A linguagem-alvo do compilador possui as seguintes características:

- Tipos primitivos: `int`, `string`, `float`
- Estruturas de controle: `if/else`, `do/while`, `repeat/until`
- Entrada e saída: `read`, `write`
- Operadores lógicos: `and`, `or`, `not`
- Comentários de uma linha (`//`) e de múltiplas linhas (`/* */`)
- Linguagem *case-sensitive*
- Todas as variáveis devem ser declaradas antes do uso

### Palavras reservadas

```
class, int, string, float, if, else, do, while,
repeat, until, read, write, and, or, not
```

### Exemplo de código válido

```
class Exemplo {
    int n, i, soma;

    write("Digite quantos numeros deseja somar: ");
    read(n);

    soma := 0;
    i := 1;

    do {
        soma := soma + i;
        i := i + 1;
    } while (i <= n);

    write("Soma: ");
    write(soma);
}
```

## Estrutura do projeto

```
shenlong/
├── include/              # Cabeçalhos (.h)
│   ├── Token.h           # Definição de tipos de tokens
│   ├── Lexer.h           # Interface do analisador léxico
│   └── SymbolTable.h     # Interface da tabela de símbolos
├── src/                  # Implementação (.cpp)
│   ├── Lexer.cpp         # Autômato de reconhecimento de tokens
│   ├── SymbolTable.cpp   # Tabela com palavras reservadas pré-carregadas
│   └── main.cpp          # Ponto de entrada do compilador
├── examples/             # Programas de teste (.txt)
│   ├── teste1.txt        # Teste com erro sintático (parêntese, atribuição)
│   ├── teste2.txt        # Teste de comentário de bloco não fechado
│   ├── teste3.txt        # Teste com string não fechada e && inválido
│   ├── teste4.txt        # Teste com múltiplos erros léxicos
│   ├── teste5.txt        # Teste com erros sintáticos/semânticos
│   └── teste6.txt        # Teste funcional (sem erros)
├── obj/                  # Gerada automaticamente (objetos de build)
├── Makefile
└── README.md
```

## Como compilar

O projeto usa `make` e é compatível com Windows, Linux e macOS.

### Pré-requisitos

- `g++` com suporte a C++17
- `make` (GNU Make no Linux/macOS, ou via MSYS2/MinGW/Chocolatey no Windows)

### Compilação

```bash
make
```

Isso gera o executável `compilador` (ou `compilador.exe` no Windows) na raiz do projeto.

### Limpeza de artefatos

```bash
make clean
```

Remove a pasta `obj/` e o executável gerado.

## Como usar

Execute o compilador passando o caminho de um arquivo fonte como argumento:

```bash
./compilador examples/teste6.txt
```

No Windows:

```bash
compilador.exe examples\teste6.txt
```

### Saída da Etapa 1

Para cada arquivo processado, o compilador exibe:

1. **Sequência de tokens** identificados, com tipo, lexema, linha e coluna
2. **Erros léxicos** encontrados (caractere inválido, string não fechada, comentário de bloco não fechado)
3. **Tabela de Símbolos** final (palavras reservadas e identificadores)

Exemplo de saída:

```
TOKENS:
Token: CLASS          | Lexema: 'class'     | Linha: 1 | Coluna: 1
Token: IDENTIFIER     | Lexema: 'Teste6'    | Linha: 1 | Coluna: 7
Token: LBRACE         | Lexema: '{'         | Linha: 1 | Coluna: 14
...
Token: END_OF_FILE    | Lexema: 'EOF'       | Linha: 25 | Coluna: 2

TABELA DE SIMBOLOS:
LEXEMA              | TIPO
-----------------------------------
class               | CLASS
int                 | INT
...
soma                | IDENTIFIER
media               | IDENTIFIER
```

## Principais componentes da implementação

- **`Token`** (`include/Token.h`) — enum com todos os tipos de tokens e estrutura de token com tipo, lexema, linha e coluna.
- **`Lexer`** (`src/Lexer.cpp`) — autômato de reconhecimento baseado em leitura caractere a caractere do arquivo fonte, com tratamento de espaços em branco, comentários de linha/bloco e geração de tokens por classificação.
- **`SymbolTable`** (`src/SymbolTable.cpp`) — tabela de símbolos implementada como `unordered_map`, pré-carregada com as 15 palavras reservadas da linguagem. Distingue palavras reservadas de identificadores no momento do `lookup`.
- **`main`** (`src/main.cpp`) — orquestra a análise: abre o arquivo, consome tokens até EOF, imprime cada token e a tabela de símbolos ao final.

## Autor

Samuel Bernardes — CEFET-MG, Engenharia de Computação
