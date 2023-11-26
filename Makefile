# Variáveis para os compiladores e opções de compilação
CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Nome do executável
EXEC = sfml-app

# Arquivos .cpp
CPP_FILES = main.cpp guarda_nivel.cpp mapa.cpp movimentos.cpp voltajogada.cpp tela.cpp grafo.cpp

# Arquivos .o
OBJ_FILES = $(CPP_FILES:.cpp=.o)

# Regra padrão
all: $(EXEC)

# Regra para o executável
$(EXEC): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(CXXFLAGS)

# Regra para os arquivos .o
%.o: %.cpp
	$(CXX) -c $< -o $@

# Regra para limpar os arquivos .o e o executável
clean:
	rm -f $(OBJ_FILES) $(EXEC)

