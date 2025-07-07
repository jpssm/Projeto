# Define o compilador
CXX = g++

# Define as flags de compilação
# -Wall: Habilita todos os avisos (boa prática!)
# -Iinclude: Adiciona o diretório 'include' para procurar arquivos de cabeçalho
# Adiciona as flags do GTK+ para o compilador (-I para includes)
CXXFLAGS = -Wall -Iinclude $(shell pkg-config --cflags gtk+-3.0)

# Define o nome do executável final
TARGET = simulador

# Diretório de objetos (onde os arquivos .o serão armazenados)
OBJ_DIR = obj

# Lista de todos os arquivos fonte (.cpp)
# Pega todos os arquivos .cpp recursivamente dentro de 'src'
SRCS = $(shell find src -name "*.cpp")

# Converte a lista de arquivos fonte em uma lista de arquivos objeto (.o)
# Substitui 'src/' por 'obj/' e '.cpp' por '.o'
OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# --- Regras de Compilação ---

# Regra principal: compila o executável
$(TARGET): $(OBJS)
	@mkdir -p $(@D) # Garante que o diretório de destino exista
	# Adiciona as flags de linkagem do GTK+ (-l para bibliotecas)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(shell pkg-config --libs gtk+-3.0)
	@echo "Executável '$(TARGET)' criado com sucesso!"

# Regra para compilar arquivos .cpp em .o
# Cria os diretórios necessários no OBJ_DIR
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D) # Cria o diretório do objeto se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilado $<"

# --- Regras Auxiliares ---

# Regra 'all': A mesma que a regra padrão, para compatibilidade
all: $(TARGET)

# Regra 'clean': Remove todos os arquivos gerados pela compilação
clean:
	@echo "Limpando arquivos gerados..."
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Limpeza concluída."

.PHONY: all clean