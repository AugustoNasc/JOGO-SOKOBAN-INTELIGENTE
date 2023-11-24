#include "grafo.hpp"

void drawGraph(const Graph& g, const std::vector<sf::Vector2f>& vertexPositions) {
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
        vertices[i].setOrigin(vertices[i].getRadius(), vertices[i].getRadius()); // Define a origem no centro do círculo
        vertices[i].setPosition(vertexPositions[i]);

        labels[i].setString(std::to_string(i));
        labels[i].setFont(font);
        labels[i].setCharacterSize(20);
        labels[i].setPosition(vertexPositions[i].x - 15, vertexPositions[i].y - 15);
    }

    // Adicione as arestas aos vértices usando a matriz de adjacência
    for (int i = 0; i < g.vertices; ++i) {
        for (int j = 0; j < g.vertices; ++j) {
            if (g.adjacencyMatrix[i][j] == 1) {
                sf::VertexArray edge(sf::Lines, 2);
                edge[0].position = vertexPositions[i];
                edge[1].position = vertexPositions[j];
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
    if (!backgroundTexture.loadFromFile("fundo.png"))
        return;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    window.draw(backgroundSprite);

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

    // Inicialize a matriz de adjacência e adicione as conexões conforme necessário
    g.adjacencyMatrix.resize(g.vertices, std::vector<int>(g.vertices, 0));
    g.adjacencyMatrix[0][1] = 1;
    g.adjacencyMatrix[0][2] = 1;
    g.adjacencyMatrix[1][2] = 1;
    g.adjacencyMatrix[1][3] = 1;
    g.adjacencyMatrix[2][3] = 1;
    g.adjacencyMatrix[3][4] = 1;
    g.adjacencyMatrix[3][6] = 1;
    g.adjacencyMatrix[4][5] = 1;
    g.adjacencyMatrix[4][6] = 1;
    g.adjacencyMatrix[5][6] = 1;
    g.adjacencyMatrix[5][8] = 1;
    g.adjacencyMatrix[6][7] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[6][10] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[7][8] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[7][10] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[8][9] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[8][11] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[9][10] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[9][11] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[10][11] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[11][12] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
    g.adjacencyMatrix[12][13] = 1; // Exemplo adicional para uma aresta que volta ao vértice 0
}

void desenha_grafo_nas_posicoes(Graph& g){
    // Gere as posições aleatórias para os vértices
    std::vector<sf::Vector2f> vertexPositions;
    float x = 50;
    float y = 50;

    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa a semente com o tempo atual
    for (int i = 0; i < g.vertices; ++i) {
        vertexPositions.push_back(sf::Vector2f(x, y));
        x = 60 + rand() % 700; // Ajuste conforme necessário
        y = 30 + rand() % 500;  // Ajuste conforme necessário
    }
    drawGraph(g, vertexPositions);
}