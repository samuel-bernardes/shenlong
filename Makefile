# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Diretórios do projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Nome do executável final (adiciona .exe no Windows)
TARGET = compilador

# Detecção de SO para comandos de shell portáveis
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
    RM = if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
    RM_TARGET = if exist "$(TARGET).exe" del /q "$(TARGET).exe"
    SHELL_CMD = cmd /C
else
    MKDIR = mkdir -p $(OBJ_DIR)
    RM = rm -rf $(OBJ_DIR)
    RM_TARGET = rm -f $(TARGET)
    SHELL_CMD =
endif

# Fontes e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Regra padrão
all: prepare $(TARGET)

# Cria a pasta de objetos se não existir (não falha se já existir)
prepare:
ifeq ($(OS),Windows_NT)
	@$(SHELL_CMD) "$(MKDIR)"
else
	@$(MKDIR)
endif

# Linka os objetos no executável final
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo Compilacao concluida. Executavel: $(TARGET)

# Compila cada .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove artefatos de build
clean:
ifeq ($(OS),Windows_NT)
	@$(SHELL_CMD) "$(RM)"
	@$(SHELL_CMD) "$(RM_TARGET)"
else
	@$(RM)
	@$(RM_TARGET)
endif
	@echo Arquivos limpos.

.PHONY: all clean prepare
