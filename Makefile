# Define o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Define os diretórios do projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Encontra todos os arquivos .cpp na pasta src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Define os nomes dos arquivos objeto (.o) correspondentes
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nome do arquivo executável final
TARGET = compilador

# A regra 'all' é a padrão que será executada ao digitar 'make'
all: prepare $(TARGET)

# Cria a pasta de objetos caso ela não exista
prepare:
	@mkdir $(OBJ_DIR)

# Regra para linkar os objetos e gerar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Compilacao concluida com sucesso! Executavel: $(TARGET)"

# Regra para compilar cada .cpp individualmente em um .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (útil para recompilar do zero)
clean:
	rmdir /s $(OBJ_DIR)
	@echo "Arquivos limpos."

# Evita conflitos com arquivos que tenham os mesmos nomes das regras
.PHONY: all clean prepare