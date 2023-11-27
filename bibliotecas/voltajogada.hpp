#ifndef VOLTAJOGADAS_HPP
#define VOLTAJOGADAS_HPP

#include "mapa.hpp"
#include <stdio.h>

namespace vtj{
    void registrando_jogadas(MAPA mapa, int level);
    void voltando_jogada(MAPA *mapa, int level, int voltando);
    void adiantando_jogada(MAPA *mapa, int level, int voltando);
    void apagar_jogadas(int level);
}

#endif