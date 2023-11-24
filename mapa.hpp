#ifndef MAPA_HPP
#define MAPA_HPP

#include <SFML/Graphics.hpp>

struct Quadrado {
    sf::Texture imagem;
    sf::Vector2f coordenada;
};

struct MAPA {
    char mapa[12][13];
    int especial_inicio[12][12];
    int especial_atual[12][12];
};

void declarar_posicoes_de_encaixe(MAPA*);
bool finalizou_mapa(MAPA);
void mapa_desenhando(int, MAPA, Quadrado*, Quadrado*, int, sf::RenderWindow&);
void mapa_declarar_imagens_usadas(Quadrado**);
void mapa_background_fundo(Quadrado**);
MAPA mapa_rezetar(int);

#endif