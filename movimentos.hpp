#ifndef MOVIMENTOS_HPP
#define MOVIMENTOS_HPP

#include "mapa.hpp"

void troca_vazio(MAPA*, int*, int*, int, int, int, int*);

void troca_caixa(int*, int*, int, int, MAPA*, int);

void mover_personagem(int*,int*,int, MAPA*, int, sf::Clock&);

void comando_por_tecla(sf::Event event, int &flag, int &voltando, int &gX, int &gY, MAPA &mapa, int level, sf::Clock &clock);

#endif