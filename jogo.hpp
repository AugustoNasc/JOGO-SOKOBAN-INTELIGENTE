#ifndef JOGO_HPP
#define JOGO_HPP

#include "bibliotecas/mapa.hpp"
#include <string>
#include <string.h>
#include <iostream>
#include "bibliotecas/movimentos.hpp"
#include "bibliotecas/voltajogada.hpp"
#include "bibliotecas/guarda_nivel.hpp"
#include "bibliotecas/tela.hpp"
#include "bibliotecas/grafo.hpp"
#include <SFML/Audio.hpp>

void carrega_jogo(sf::RenderWindow &, GameScreen &, sf::Clock &, int &, int &, 
                    int &, bool [], MAPA &, int *, 
                    char [],
                    direcaoPersonagem &, Quadrado *, Quadrado *, int &, int&);

void toca_musica(std::string);
#endif