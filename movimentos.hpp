#ifndef MOVIMENTOS_HPP
#define MOVIMENTOS_HPP

#include "mapa.hpp"

void troca_vazio(MAPA*, int*, int*, int, int, int, int*);

void troca_caixa(int*, int*, int, int, MAPA*, int);

void mover_personagem(int*,int*,int, MAPA*, int, sf::Clock&);

#endif