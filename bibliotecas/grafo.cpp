#include "grafo.hpp"
#include <queue>
#include <limits>
#include <cmath>
#include <iostream>
#include "movimentos.hpp"
#include "guarda_nivel.hpp"

void desenhaGrafo_e_direcionaMapa(const Graph& g, sf::RenderWindow &window, MAPA &mapa, GameScreen &currentScreen,
                                 int &gX, int &gY, int &level, bool mapa_acessado[], int *verticeAtualPersonagem, int forca) {

    std::vector<sf::CircleShape> vertices(g.vertices);
    std::vector<sf::Text> labels(g.vertices);
    std::vector<sf::VertexArray> edges;


    sf::Font font;
    if (!font.loadFromFile("assets/arial_narrow_7.ttf")) {
        std::cerr << "Erro ao carregar a fonte\n";
        return;
    }

    for (int i = 0; i < g.vertices; ++i) {
        vertices[i].setRadius(30);
        if(mapa_acessado[i]) vertices[i].setFillColor(sf::Color::Green) ;
        else if(forca<i+1) vertices[i].setFillColor(sf::Color::Red);
        else vertices[i].setFillColor(sf::Color::Blue);
        vertices[i].setOrigin(vertices[i].getRadius(), vertices[i].getRadius());
        vertices[i].setPosition(g.verticesInfo[i].position);

        labels[i].setString(std::to_string(i+1));
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

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/fundo.png")){
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

        sf::Texture characterTexture;
        // Carregue a textura do personagem
        if (!characterTexture.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_1.png")) {
            std::cerr << "Erro ao carregar a textura do personagem\n";
            return;
        }

        sf::Sprite character(characterTexture);
        character.setScale(1, 1);  // Ajuste conforme necessário

        // Desenhe o personagem no vértice atual
        sf::Vector2f characterPosition = g.verticesInfo[*verticeAtualPersonagem].position;
        character.setPosition(characterPosition - sf::Vector2f(25, 25));  // Ajuste conforme necessário
        window.draw(character);
        /*mv::anda_pelos_vertices(window, g, character, vertices, labels, edges, characterPosition, verticeAtualPersonagem, ultimo_nivel_desbloqueado()-1);
        *verticeAtualPersonagem=ultimo_nivel_desbloqueado()-1;*/

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < g.vertices; ++i) {
                        sf::Vector2f vertexPos = g.verticesInfo[i].position;
                        float distance = std::sqrt(std::pow(mousePos.x - vertexPos.x, 2) +
                                                  std::pow(mousePos.y - vertexPos.y, 2));

                        if (distance <= 50) {  // Raio do círculo (raio dos vértices)
                            // Adicione aqui qualquer ação que deseja executar ao clicar no vértice

                            int destino = i;
                            mv::anda_pelos_vertices(window, g, character, vertices, labels, edges, characterPosition, verticeAtualPersonagem, destino);

                            char endereco[50];
                            sprintf(endereco, "mapastxt/mapa%d.txt", i+1);
                            level=i+1;
                            FILE *arquivo = fopen(endereco, "rt");
                            fread(mapa.mapa, sizeof(char), 12*13, arquivo);
                            declarar_posicoes_de_encaixe(&mapa);

                            currentScreen = GAMEPLAY;
                            //atualiza_posicao_jogador(gX, gY, mapa);
                            //sentido=FRENTE;
                        }
                    }
                }
            }
        }
        window.display();
}

void grafo_do_jogo(Graph& g){
    g.vertices = 13;

    float x = 50;
    float y = 50;

    x+=120;
    y+=10;
    g.verticesInfo.push_back({sf::Vector2f(x, y)});
    
    x+=150;
    y+=30;
    g.verticesInfo.push_back({sf::Vector2f(x, y)});

    x+=160;
    y-=10;
    g.verticesInfo.push_back({sf::Vector2f(x, y)});

    for (int i = 3; i < g.vertices; ++i) {
        x+=120;
        y+=10;
        if(x>=580){
            x=50;
            y+=150;
        }
        g.verticesInfo.push_back({sf::Vector2f(x, y)});
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
    colocar_peso_aresta(g, 1, 2);
    colocar_peso_aresta(g, 1, 3);
    colocar_peso_aresta(g, 2, 7);
    colocar_peso_aresta(g, 3, 4);
    colocar_peso_aresta(g, 4, 5);
    colocar_peso_aresta(g, 5, 6);
    colocar_peso_aresta(g, 5, 8);
    colocar_peso_aresta(g, 5, 10); 
    colocar_peso_aresta(g, 6, 7); 
    colocar_peso_aresta(g, 7, 10);
    colocar_peso_aresta(g, 8, 9); 
    colocar_peso_aresta(g, 9, 10);
    colocar_peso_aresta(g, 10, 11);
    colocar_peso_aresta(g, 11, 12);
}

void colocar_peso_aresta(Graph& g, int i, int j){
    float distance = std::sqrt(std::pow(g.verticesInfo[i].position.x - g.verticesInfo[j].position.x, 2) +\
                                           std::pow(g.verticesInfo[i].position.y - g.verticesInfo[j].position.y, 2));
    g.adjacencyMatrix[i][j] = static_cast<int>(distance);

    g.adjacencyMatrix[j][i] = static_cast<int>(distance);
}

/* std::vector<int> dijkstra(const Graph& g, int verticeInicial) {

    std::vector<int> dist(g.vertices, std::numeric_limits<int>::max());
    dist[verticeInicial] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, verticeInicial});

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
} */

std::vector<int> menorCaminho(const Graph& g, int verticeInicial, int destino) {
    std::vector<int> dist(g.vertices, std::numeric_limits<int>::max());
    std::vector<int> prev(g.vertices, -1);
    std::vector<bool> visitado(g.vertices, false);

    dist[verticeInicial] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, verticeInicial});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        for (int v = 0; v < g.vertices; ++v) {
            if (g.adjacencyMatrix[u][v] > 0) {
                int weight = g.adjacencyMatrix[u][v];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    std::vector<int> caminho;
    for (int v = destino; v != -1; v = prev[v])
        caminho.push_back(v);
    std::reverse(caminho.begin(), caminho.end());

    return caminho;
}
