#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

struct Vertex {
    sf::Vector2f position;
};

struct Graph {
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix; // Matriz de adjacência para representar as conexões
    std::vector<Vertex> verticesInfo;
};

void drawGraph(const Graph& g);
void grafo_do_jogo(Graph& g);
void desenha_grafo_nas_posicoes(Graph& g);
void colocar_peso_aresta(Graph& g, int i, int j);
std::vector<int> dijkstra(const Graph& g, int source);

#endif