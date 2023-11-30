# Variáveis para os compiladores e as flags de compilação
CXX = g++
CXXFLAGS = -Wall -g

# Variáveis para as bibliotecas do SFML
SFML_LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Variável para a pasta das bibliotecas
LIB_DIR = bibliotecas

# Nome do arquivo executável
EXEC = Sokoban

# Regra padrão
all: $(EXEC)

# Regra para o arquivo executável
$(EXEC): main.o jogo.o mapa.o movimentos.o voltajogada.o guarda_nivel.o tela.o grafo.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

# Regra para o arquivo objeto da main
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regras para os arquivos objeto das bibliotecas
mapa.o: $(LIB_DIR)/mapa.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

movimentos.o: $(LIB_DIR)/movimentos.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

voltajogada.o: $(LIB_DIR)/voltajogada.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

guarda_nivel.o: $(LIB_DIR)/guarda_nivel.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tela.o: $(LIB_DIR)/tela.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

grafo.o: $(LIB_DIR)/grafo.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -f *.o $(EXEC)
