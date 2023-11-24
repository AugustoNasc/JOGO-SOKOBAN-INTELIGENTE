#include "grafo.hpp"
#include <queue>
#include <limits>
#include <cmath>
#include <iostream>

void drawGraph(const Graph& g) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    std::vector<sf::CircleShape> vertices(g.vertices);
    std::vector<sf::Text> labels(g.vertices);
    std::vector<sf::VertexArray> edges;

    sf::Font font;
    if (!font.loadFromFile("arial_narrow_7.ttf")) {
        std::cerr << "Erro ao carregar a fonte\n";
        return;
    }

    for (int i = 0; i < g.vertices; ++i) {
        vertices[i].setRadius(30);
        vertices[i].setFillColor(sf::Color::Blue);
        vertices[i].setOrigin(vertices[i].getRadius(), vertices[i].getRadius());
        vertices[i].setPosition(g.verticesInfo[i].position);

        labels[i].setString(std::to_string(i));
        labels[i].setFont(font);
        labels[i].setCharacterSize(15);
        labels[i].setPosition(g.verticesInfo[i].position.x - 30, g.verticesInfo[i].position.y - 40);
    }

    // Adicione as arestas aos vértices usando a matriz de adjacência
    for (int i = 0; i < g.vertices; ++i) {
        for (int j = 0; j < g.vertices; ++j) {
            if (g.adjacencyMatrix[i][j] > 0) {
                sf::VertexArray edge(sf::Lines, 2);
                edge[0].position = g.verticesInfo[i].position;
                edge[1].position = g.verticesInfo[j].position;
                edge[0].color = sf::Color::White;
                edge[1].color = sf::Color::White;
                edges.push_back(edge);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("fundo.png")){
            //erro...
        }

        sf::Sprite background(backgroundTexture);
        window.draw(background);

        // Desenhe as arestas
        for (const auto& edge : edges) {
            window.draw(edge);
        }

        // Desenhe os vértices e rótulos
        for (int i = 0; i < g.vertices; ++i) {
            window.draw(vertices[i]);
            window.draw(labels[i]);
        }

        window.display();
    }
}

void grafo_do_jogo(Graph& g){
    g.vertices = 13;

    float x = 50;
    float y = 50;

    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa a semente com o tempo atual
    for (int i = 0; i < g.vertices; ++i) {
        g.verticesInfo.push_back({sf::Vector2f(60 + rand() % 700, 30 + rand() % 500)});
    }

    // Inicialize a matriz de adjacência e adicione as conexões conforme necessário
    g.adjacencyMatrix.resize(g.vertices, std::vector<int>(g.vertices, 0));

    for (int i = 0; i < g.vertices; ++i) {
        for (int j = 0; j < g.vertices; ++j) {
            if (i != j) {
                g.adjacencyMatrix[i][j] = 0;
            }
        }
    }

    colocar_peso_aresta(g, 0, 1);
    colocar_peso_aresta(g, 0, 1);
    colocar_peso_aresta(g, 0, 2);
    colocar_peso_aresta(g, 1, 2);
    colocar_peso_aresta(g, 1, 3);
    colocar_peso_aresta(g, 2, 3);
    colocar_peso_aresta(g, 3, 4);
    colocar_peso_aresta(g, 3, 6);
    colocar_peso_aresta(g, 4, 5);
    colocar_peso_aresta(g, 4, 6);
    colocar_peso_aresta(g, 5, 6);
    colocar_peso_aresta(g, 5, 8);
    colocar_peso_aresta(g, 6, 7); 
    colocar_peso_aresta(g, 6, 10);
    colocar_peso_aresta(g, 7, 8); 
    colocar_peso_aresta(g, 7, 10);
    colocar_peso_aresta(g, 8, 9); 
    colocar_peso_aresta(g, 8, 11);
    colocar_peso_aresta(g, 9, 10);
    colocar_peso_aresta(g, 9, 11);
    colocar_peso_aresta(g, 10, 11);
    colocar_peso_aresta(g, 11, 12);
    colocar_peso_aresta(g, 12, 13);
}

void desenha_grafo_nas_posicoes(Graph& g){
    // Gere as posições aleatórias para os vértices
    std::vector<sf::Vector2f> vertexPositions;
    for (int i = 0; i < g.vertices; ++i) {
        vertexPositions.push_back(g.verticesInfo[i].position);
    }
    drawGraph(g);
}


void colocar_peso_aresta(Graph& g, int i, int j){
    float distance = std::sqrt(std::pow(g.verticesInfo[i].position.x - g.verticesInfo[j].position.x, 2) +\
                                           std::pow(g.verticesInfo[i].position.y - g.verticesInfo[j].position.y, 2));
    g.adjacencyMatrix[i][j] = static_cast<int>(distance);
}

std::vector<int> dijkstra(const Graph& g, int source) {
    std::vector<int> dist(g.vertices, std::numeric_limits<int>::max());
    dist[source] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < g.vertices; ++v) {
            if (g.adjacencyMatrix[u][v] > 0) {
                int weight = g.adjacencyMatrix[u][v];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return dist;
}

/*
void grafo_do_jogo(Graph& g){
    g.vertices = 13;

    float x = 50;
    float y = 50;

    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa a semente com o tempo atual
    for (int i = 0; i < g.vertices; ++i) {
        g.verticesInfo[i].position.x = 60 + rand() % 700; // Ajuste conforme necessário
        g.verticesInfo[i].position.y = 30 + rand() % 500;  // Ajuste conforme necessário
    }

    for (int i = 0; i < g.vertices; ++i) {
        for (int j = 0; j < g.vertices; ++j) {
            if (i != j) {
                g.adjacencyMatrix[i][j] = 0;
            }
        }
    }
    // Inicialize a matriz de adjacência e adicione as conexões conforme necessário
    g.adjacencyMatrix.resize(g.vertices, std::vector<int>(g.vertices, 0));
    colocar_peso_aresta(g, 0, 1);
    //g.adjacencyMatrix[0][1] = 1;
    //g.adjacencyMatrix[0][2] = 1;
    //g.adjacencyMatrix[1][2] = 1;
    //g.adjacencyMatrix[1][3] = 1;
    //g.adjacencyMatrix[2][3] = 1;
    //g.adjacencyMatrix[3][4] = 1;
    //g.adjacencyMatrix[3][6] = 1;
    //g.adjacencyMatrix[4][5] = 1;
    //g.adjacencyMatrix[4][6] = 1;
    //g.adjacencyMatrix[5][6] = 1;
    //g.adjacencyMatrix[5][8] = 1;
    //g.adjacencyMatrix[6][7] = 1; 
    //g.adjacencyMatrix[6][10] = 1;
    //g.adjacencyMatrix[7][8] = 1; 
    //g.adjacencyMatrix[7][10] = 1;
    //g.adjacencyMatrix[8][9] = 1; 
    //g.adjacencyMatrix[8][11] = 1;
    //g.adjacencyMatrix[9][10] = 1;
    //g.adjacencyMatrix[9][11] = 1;
    //g.adjacencyMatrix[10][11] = 1;
    //g.adjacencyMatrix[11][12] = 1;
    //g.adjacencyMatrix[12][13] = 1;
}*/