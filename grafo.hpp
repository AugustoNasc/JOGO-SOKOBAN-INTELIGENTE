#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

struct Graph {
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix; // Matriz de adjacência para representar as conexões
};

void drawGraph(const Graph& g, const std::vector<sf::Vector2f>& vertexPositions);
void grafo_do_jogo(Graph& g);
void desenha_grafo_nas_posicoes(Graph& g);

#endif