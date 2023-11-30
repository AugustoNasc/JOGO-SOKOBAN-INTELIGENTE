#include <stdio.h>
#include "movimentos.hpp"
#include "voltajogada.hpp"
#include "tela.hpp"
#include <iostream>
#include <cmath>

#define QTD_QUADRADOS 12

namespace mv{
    void atualiza_posicao_jogador(int& x, int& y, MAPA mapa){
                for(int i=0; i<QTD_QUADRADOS; i++){
                        for(int j=0; j<QTD_QUADRADOS; j++){
                            if(mapa.mapa[i][j]=='P'){
                            y=i; x=j;
                            }
                        }
                }
    }

    void empurra_vazio(MAPA &mapa, int &x, int &y, int cont1, int cont2, int level, int &ja_andou){

                char aux;
                if ((mapa).mapa[y+cont2][x+cont1] == '@'||(mapa).mapa[y+cont2][x+cont1] == '+'){
                    aux = (mapa).mapa[y+cont2][x+cont1];
                    (mapa).mapa[y+cont2][x+cont1]=(mapa).mapa[y][x];
                    (mapa).mapa[y][x]= aux;
                    x=x+cont1; y=y+cont2;
                    vtj::registrando_jogadas(mapa, level);
                    ja_andou=1;
                }
    }

    void empurra_caixa(int &x, int &y, int cont1, int cont2, MAPA &mapa, int level){

    if(x+2*cont1>=0 && x+2*cont1<12 && y+2*cont2>=0 && y+2*cont2<12){

            if((mapa).mapa[y+cont2][x+cont1] == 'B'){

                if ((mapa).mapa[y+2*cont2][x+2*cont1] == '@'||(mapa).mapa[y+2*cont2][x+2*cont1] == '+'){
                        if((mapa).especial_atual[y+2*cont2][x+2*cont1]==1){
                            (mapa).especial_atual[y+2*cont2][x+2*cont1]=0;
                        }
                        if((mapa).especial_atual[y+cont2][x+cont1]==0){
                            if((mapa).especial_inicio[y+cont2][x+cont1]==1){
                            (mapa).especial_atual[y+cont2][x+cont1]=1;}
                        }
                        (mapa).mapa[y+2*cont2][x+2*cont1]='B';
                        (mapa).mapa[y+cont2][x+cont1]='P';
                        (mapa).mapa[y][x]= '@';
                        y=y+cont2;
                        x=x+cont1;  
                        vtj::registrando_jogadas(mapa, level);

                }
            }
    }

    }

    void mover_personagem(int &x,int &y,direcaoPersonagem &sentido, MAPA &mapa, int level, sf::Clock &clock){
        sf::Time elapsed = clock.getElapsedTime();
        if((mapa).mapa[y][x]=='P'&& elapsed.asSeconds() >= 0.01f){

        int ja_andou=0;
        int cont1, cont2;
        if(sentido == 1)
        {
        cont1=-1; cont2=0;
        if(x+cont1>=0 && x+cont1<12 && y+cont2>=0 && y+cont2<12){
            empurra_vazio(mapa, x, y, cont1, cont2, level, ja_andou);}

        if(x+2*cont1>=0 && x+2*cont1<12 && y+2*cont2>=0 && y+2*cont2<12 && !ja_andou){
            empurra_caixa(x, y, cont1, cont2, mapa, level);}


        }
    
        else if(sentido == 2)
        {
            cont1=1; cont2=0;
        if(x+cont1>=0 && x+cont1<12 && y+cont2>=0 && y+cont2<12){
            empurra_vazio(mapa, x, y, cont1, cont2, level, ja_andou);}

        if(x+2*cont1>=0 && x+2*cont1<12 && y+2*cont2>=0 && y+2*cont2<12&& !ja_andou){
            empurra_caixa(x, y, cont1, cont2, mapa, level); }


        }
        else if(sentido == 3)
        {
            cont1=0; cont2=1;
        if(x+cont1>=0 && x+cont1<12 && y+cont2>=0 && y+cont2<12){
            empurra_vazio(mapa, x, y, cont1, cont2, level, ja_andou); }

        if(x+2*cont1>=0 && x+2*cont1<12 && y+2*cont2>=0 && y+2*cont2<12&& !ja_andou){
            empurra_caixa(x, y, cont1, cont2, mapa, level);}


        }
    
        else if(sentido == 4)
        {
            cont1=0; cont2=-1;
        if(x+cont1>=0 && x+cont1<12 && y+cont2>=0 && y+cont2<12){
            empurra_vazio(mapa, x, y, cont1, cont2, level, ja_andou); }

        if(x+2*cont1>=0 && x+2*cont1<12 && y+2*cont2>=0 && y+2*cont2<12&& !ja_andou){
            empurra_caixa(x, y, cont1, cont2, mapa, level);}


        }
        clock.restart();
        }
    }

    void comando_por_tecla(sf::Event event, direcaoPersonagem& sentido, int &voltando, int &gX, int &gY, MAPA &mapa, int &level, sf::Clock &clock){
                        char endereco[50];
                        FILE *arquivo;

                        if((event.key.code==sf::Keyboard::A)||(event.key.code==sf::Keyboard::Left)){ 
                            sentido=ESQUERDA; 
                            voltando=0;
                            mover_personagem(gX, gY, sentido, mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::D)||(event.key.code==sf::Keyboard::Right)){ 
                            sentido=DIREITA;
                            voltando=0;
                            mover_personagem(gX, gY, sentido, mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::S)||(event.key.code==sf::Keyboard::Down)){ 
                            sentido=BAIXO;
                            voltando=0;
                            mover_personagem(gX, gY, sentido, mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::W)||(event.key.code==sf::Keyboard::Up)){ 
                            sentido=CIMA; 
                            voltando=0;
                            mover_personagem(gX, gY, sentido, mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::Z)){ 
                            vtj::voltando_jogada(&mapa, level, voltando);
                            voltando++;
                            sentido=FRENTE;
                            //atualiza_posicao_jogador(gX, gY,mapa);
                        }

                        else if((event.key.code==sf::Keyboard::C)){ 
                            if(voltando!=0){
                                vtj::adiantando_jogada(&mapa, level, voltando);
                                voltando--;
                                sentido=FRENTE;
                                atualiza_posicao_jogador(gX, gY, mapa);
                            }
                        }
                        else if((event.key.code==sf::Keyboard::X)){ 

                            mapa = mapa_rezetar(level);

                            declarar_posicoes_de_encaixe(&mapa);

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;

                        }
    
                        //provisorio, so para admins
                        else if((event.key.code==sf::Keyboard::P)&&level!=13){ 
                            vtj::apagar_jogadas(level);
                            level++;

                            sprintf(endereco, "mapastxt/mapa%d.txt", level);

                            arquivo = fopen(endereco, "rt");

                            fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                            declarar_posicoes_de_encaixe(&mapa);

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;
                            
                        }

                        else if((event.key.code==sf::Keyboard::O)&&level!=1){ 
                            vtj::apagar_jogadas(level);
                            level--;

                            sprintf(endereco, "mapastxt/mapa%d.txt", level);

                            arquivo = fopen(endereco, "rt");

                            fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                            declarar_posicoes_de_encaixe(&mapa);

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;
                        }
    }

void anda_pelos_vertices(sf::RenderWindow& window, const Graph& g, sf::Sprite& character,
                         std::vector<sf::CircleShape>& vertices, std::vector<sf::Text>& labels,
                         std::vector<sf::VertexArray>& edges, sf::Vector2f& characterPosition,
                         int *verticeAtualPersonagem, int destino) {

                        std::vector<int> caminho = menorCaminho(g, *verticeAtualPersonagem, destino);

                        float speed = 200.0f;
                        sf::Texture backgroundTexture;
                                if (!backgroundTexture.loadFromFile("assets/fundo.png")){
                                //erro...
                                }

                                sf::Sprite background(backgroundTexture);

                        for (std::size_t i = 1; i < caminho.size(); ++i) {
                            int currentVertex = caminho[i - 1];
                            int nextVertex = caminho[i];

                            sf::Vector2f currentPos = g.verticesInfo[currentVertex].position;
                            sf::Vector2f nextPos = g.verticesInfo[nextVertex].position;

                            sf::Vector2f direction = nextPos - currentPos;
                            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                            direction /= distance;  // Normalização do vetor

                            sf::Clock timer;
                            float elapsedSeconds = 0.0f;

                            while (elapsedSeconds < distance / speed) {
                                float deltaTime = timer.restart().asSeconds();
                                elapsedSeconds += deltaTime;

                                characterPosition += direction * speed * deltaTime;

                                window.clear();
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

                                character.setPosition(characterPosition - sf::Vector2f(25, 25));
                                window.draw(character);
                                window.display();

                                sf::sleep(sf::milliseconds(20));

                                sf::Event event;
                                while (window.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        window.close();
                                        return;
                                    }
                                }
                            }

                            // Atualize a posição do personagem para o próximo vértice ao final do loop
                            characterPosition = nextPos;
                        }

}



}
