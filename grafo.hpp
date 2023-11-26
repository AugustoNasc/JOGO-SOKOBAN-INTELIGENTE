#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "mapa.hpp"
#include "tela.hpp"

struct Vertex {
    sf::Vector2f position;
};

struct Graph {
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix; // Matriz de adjacência para representar as conexões
    std::vector<Vertex> verticesInfo;
};

void desenhaGrafo_e_direcionaMapa(const Graph&, sf::RenderWindow &, MAPA &, GameScreen &,  int &, int &, int &level);
void grafo_do_jogo(Graph&);
//void desenha_grafo_nas_posicoes(Graph&, sf::RenderWindow &, MAPA &, GameScreen &, int &, int &, int &level);
void colocar_peso_aresta(Graph&, int, int);
std::vector<int> dijkstra(const Graph&, int);

#endif