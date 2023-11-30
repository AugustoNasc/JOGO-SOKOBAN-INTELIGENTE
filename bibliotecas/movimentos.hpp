#ifndef MOVIMENTOS_HPP
#define MOVIMENTOS_HPP

#include "grafo.hpp"
#include "mapa.hpp"

namespace mv{
    void atualiza_posicao_jogador(int&, int&, MAPA);

    void empurra_vazio(MAPA&, int&, int&, int, int, int, int&);
    void empurra_caixa(int&, int&, int, int, MAPA&, int, int, sf::RenderWindow&);

    void mover_personagem(int&,int&,direcaoPersonagem&, MAPA&, int, sf::Clock&, int forca, sf::RenderWindow&);
    void comando_por_tecla(sf::Event, direcaoPersonagem &, int &, int &, int &, MAPA &, int&, sf::Clock &, int &forca, sf::RenderWindow&);
    void anda_pelos_vertices(sf::RenderWindow& window, const Graph& g, sf::Sprite& character,
                            std::vector<sf::CircleShape>& vertices, std::vector<sf::Text>& labels,
                            std::vector<sf::VertexArray>& edges, sf::Vector2f& characterPosition, int *, int destino);
}

#endif