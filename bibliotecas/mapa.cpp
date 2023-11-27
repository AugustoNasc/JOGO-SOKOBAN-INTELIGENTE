#include <SFML/Graphics.hpp>
#include <string>
#include "mapa.hpp"
#include "voltajogada.hpp"

#define QTD_QUADRADOS 12
#define LARGURA 600
#define DIMENSAO LARGURA/QTD_QUADRADOS
#define PINTAR(figura) (figura).coordenada.x = k*DIMENSAO; \
                          (figura).coordenada.y = j*DIMENSAO; \
                          \
                          if(sentido==1){ (figura).coordenada.x-=15; } \
                          if(sentido==2){ (figura).coordenada.x+=6; } \
                          \
                          sprite.setTexture((figura).imagem); \
                          sprite.setTextureRect(sf::IntRect(0, 0, DIMENSAO, DIMENSAO)); \
                          sprite.setPosition((figura).coordenada.x, (figura).coordenada.y); \
                          window.draw(sprite);

void declarar_posicoes_de_encaixe(MAPA *mapa) {
    for(int i=0; i<QTD_QUADRADOS; i++) {
        for(int j=0; j<QTD_QUADRADOS; j++) {
            if((*mapa).mapa[i][j]=='+') {
                (*mapa).especial_inicio[i][j]=1;
                (*mapa).especial_atual[i][j]=1;
            } else {
                (*mapa).especial_inicio[i][j]=0;
                (*mapa).especial_atual[i][j]=0;
            }
        }
    }
}

bool finalizou_mapa(MAPA mapa) {
    int contador=0;
    for(int i=0; i<QTD_QUADRADOS; i++) {
        for(int k=0; k<QTD_QUADRADOS; k++) {
            if(mapa.especial_atual[i][k]==1) {
                contador++;
            }
        }
    }
    if(contador==0)
        return true;
     
    return false;
}

void mapa_declarar_imagens_usadas(Quadrado **imagens) {
    (*imagens)[0].imagem.loadFromFile("assets/mapa/adicionado mapa/crate_12.png"); //box
    (*imagens)[1].imagem.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_1.png"); //p
    (*imagens)[2].imagem.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_5.png"); //pa
    (*imagens)[3].imagem.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_6.png"); //pd
    (*imagens)[4].imagem.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_2.png"); //ps
    (*imagens)[5].imagem.loadFromFile("assets/mapa/adicionado mapa/Layer 2_sprite_4.png"); //pw
}

void mapa_background_fundo(Quadrado **fundo) {
    char endereco[50];

    for(int level=1; level<=13; level++) {
        sprintf(endereco, "assets/mapa/mapa%d.png", level);
        (*fundo)[level-1].imagem.loadFromFile(endereco);
    }
}

void mapa_desenhando(direcaoPersonagem &sentido, MAPA mapa, Quadrado *imagens, Quadrado *fundo, int level, sf::RenderWindow &window) {
    sf::Sprite sprite;

    (fundo[level-1]).coordenada = sf::Vector2f(0, 0);
    sprite.setTexture((fundo[level-1]).imagem);
    sprite.setTextureRect(sf::IntRect(0, 0, LARGURA, LARGURA));
    sprite.setPosition((fundo[level-1]).coordenada.x, (fundo[level-1]).coordenada.y);
    window.draw(sprite);

    for(int j=0; j<QTD_QUADRADOS; j++) {
        for(int k=0; k<QTD_QUADRADOS; k++) {
            if(mapa.mapa[j][k]=='P') {
                if(sentido==FRENTE) {
                    PINTAR(imagens[1]);
                } else if(sentido==ESQUERDA) {
                    PINTAR(imagens[2]);
                } else if(sentido==DIREITA) {
                    PINTAR(imagens[3]);
                } else if(sentido==BAIXO) {
                    PINTAR(imagens[4]);
                } else if(sentido==CIMA) {
                    PINTAR(imagens[5]);
                }
            }

            if(mapa.mapa[j][k]=='B') { //box
                (imagens[0]).coordenada = sf::Vector2f(k*(DIMENSAO)+3, j*(DIMENSAO)+3);
                sprite.setTexture((imagens[0]).imagem);
                sprite.setTextureRect(sf::IntRect(0, 0, DIMENSAO-7, DIMENSAO-7));
                sprite.setPosition((imagens[0]).coordenada.x, (imagens[0]).coordenada.y);
                window.draw(sprite);
            }
        }
    }
}

MAPA mapa_rezetar(int level) {
    char endereco[50];
    MAPA mapa_rezetado;
    FILE *arquivo;
    vtj::apagar_jogadas(level);
    sprintf(endereco, "mapastxt/mapa%d.txt", level);
    arquivo = fopen(endereco, "rt");
    fread(mapa_rezetado.mapa, sizeof(char), 12*13, arquivo);
    declarar_posicoes_de_encaixe(&mapa_rezetado);
    fclose(arquivo);
    return mapa_rezetado;
}