#include <stdio.h>
#include "movimentos.hpp"
#include "voltajogada.hpp"
#include "tela.hpp"
#include <iostream>
#include <cmath>

#define QTD_QUADRADOS 12

/* class JOGO{
    public:
        int gX, gY;
        MAPA mapa;
        direcaoPersonagem sentido = FRENTE;
        JOGO(){
            sentido = FRENTE;
            gX=0; gY=0;
            declarar_posicoes_de_encaixe(&mapa);
            atualiza_posicao_jogador(gX, gY, mapa);
        }
};*/

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

    void troca_vazio(MAPA *mapa, int *x, int *y, int cont1, int cont2, int level, int *ja_andou){

                char aux;
                if ((*mapa).mapa[*y+cont2][*x+cont1] == '@'||(*mapa).mapa[*y+cont2][*x+cont1] == '+'){
                    aux = (*mapa).mapa[*y+cont2][*x+cont1];
                    (*mapa).mapa[*y+cont2][*x+cont1]=(*mapa).mapa[*y][*x];
                    (*mapa).mapa[*y][*x]= aux;
                    *x=*x+cont1; *y=*y+cont2;
                    registrando_jogadas(*mapa, level);
                    *ja_andou=1;
                }
    }

    void troca_caixa(int *x, int *y, int cont1, int cont2, MAPA *mapa, int level){

    if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12){

            if((*mapa).mapa[*y+cont2][*x+cont1] == 'B'){

                if ((*mapa).mapa[*y+2*cont2][*x+2*cont1] == '@'||(*mapa).mapa[*y+2*cont2][*x+2*cont1] == '+'){
                        if((*mapa).especial_atual[*y+2*cont2][*x+2*cont1]==1){
                            (*mapa).especial_atual[*y+2*cont2][*x+2*cont1]=0;
                        }
                        if((*mapa).especial_atual[*y+cont2][*x+cont1]==0){
                            if((*mapa).especial_inicio[*y+cont2][*x+cont1]==1){
                            (*mapa).especial_atual[*y+cont2][*x+cont1]=1;}
                        }
                        (*mapa).mapa[*y+2*cont2][*x+2*cont1]='B';
                        (*mapa).mapa[*y+cont2][*x+cont1]='P';
                        (*mapa).mapa[*y][*x]= '@';
                        *y=*y+cont2;
                        *x=*x+cont1;  
                        registrando_jogadas(*mapa, level);

                }
            }
    }

    }

    void mover_personagem(int *x,int *y,direcaoPersonagem &sentido, MAPA *mapa, int level, sf::Clock &clock){
        sf::Time elapsed = clock.getElapsedTime();
        if((*mapa).mapa[*y][*x]=='P'&& elapsed.asSeconds() >= 0.01f){

        int ja_andou=0;
        int cont1, cont2;
        if(sentido == 1)
        {
        cont1=-1; cont2=0;
        if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
            troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou);}

        if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12 && !ja_andou){
            troca_caixa(x, y, cont1, cont2, mapa, level);}


        }
    
        else if(sentido == 2)
        {
            cont1=1; cont2=0;
        if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
            troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou);}

        if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
            troca_caixa(x, y, cont1, cont2, mapa, level); }


        }
        else if(sentido == 3)
        {
            cont1=0; cont2=1;
        if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
            troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou); }

        if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
            troca_caixa(x, y, cont1, cont2, mapa, level);}


        }
    
        else if(sentido == 4)
        {
            cont1=0; cont2=-1;
        if(*x+cont1>=0 && *x+cont1<12 && *y+cont2>=0 && *y+cont2<12){
            troca_vazio(mapa, x, y, cont1, cont2, level, &ja_andou); }

        if(*x+2*cont1>=0 && *x+2*cont1<12 && *y+2*cont2>=0 && *y+2*cont2<12&& !ja_andou){
            troca_caixa(x, y, cont1, cont2, mapa, level);}


        }
        clock.restart();
        }
    }

    void comando_por_tecla(sf::Event event, direcaoPersonagem& sentido, int &voltando, int &gX, int &gY, MAPA &mapa, int level, sf::Clock &clock){
                        if((event.key.code==sf::Keyboard::A)||(event.key.code==sf::Keyboard::Left)){ 
                            sentido=ESQUERDA; 
                            voltando=0;
                            mover_personagem(&gX, &gY, sentido, &mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::D)||(event.key.code==sf::Keyboard::Right)){ 
                            sentido=DIREITA;
                            voltando=0;
                            mover_personagem(&gX, &gY, sentido, &mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::S)||(event.key.code==sf::Keyboard::Down)){ 
                            sentido=BAIXO;
                            voltando=0;
                            mover_personagem(&gX, &gY, sentido, &mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::W)||(event.key.code==sf::Keyboard::Up)){ 
                            sentido=CIMA; 
                            voltando=0;
                            mover_personagem(&gX, &gY, sentido, &mapa, level, clock);
                        }

                        else if((event.key.code==sf::Keyboard::Z)){ 
                            voltando_jogada(&mapa, level, voltando);
                            voltando++;
                            sentido=FRENTE;
                            //atualiza_posicao_jogador(gX, gY, mapa);
                        }

                        else if((event.key.code==sf::Keyboard::C)){ 
                            if(voltando!=0){
                                adiantando_jogada(&mapa, level, voltando);
                                voltando--;
                                sentido=FRENTE;
                                atualiza_posicao_jogador(gX, gY, mapa);
                            }
                        }
                        else if((event.key.code==sf::Keyboard::X)){ 

                            mapa = mapa_rezetar(level);

                            declarar_posicoes_de_encaixe(&mapa);

                            //jogando.stop();

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;

                            //jogando.play();
                        }
    }
                        //provisorio, so para admins
                        /*else if((event.key.code==sf::Keyboard::P)&&level!=13){ 
                            apagar_jogadas(level);
                            level++;

                            sprintf(endereco, "mapastxt/mapa%d.txt", level);

                            arquivo = fopen(endereco, "rt");

                            fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                            declarar_posicoes_de_encaixe(&mapa);

                            StopMusicStream(jogando);

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;

                            PlayMusicStream(jogando);
                        }

                        else if((event.key.code==sf::Keyboard::O)&&level!=1){ 
                            apagar_jogadas(level);
                            level--;

                            sprintf(endereco, "mapastxt/mapa%d.txt", level);

                            arquivo = fopen(endereco, "rt");

                            fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                            declarar_posicoes_de_encaixe(&mapa);

                            StopMusicStream(jogando);

                            atualiza_posicao_jogador(gX, gY, mapa);
                            sentido=FRENTE;

                            PlayMusicStream(jogando);
                        }*/
    //}

    void anda_pelos_vertices(sf::RenderWindow& window, const Graph& g, sf::Sprite& character, std::vector<sf::CircleShape> vertices,
                            std::vector<sf::Text> labels, std::vector<sf::VertexArray> edges, sf::Vector2f& characterPosition) {
        
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/fundo.png")) {
            std::cerr << "Erro ao carregar a textura do fundo\n";
            return;
        }

        sf::Sprite background(backgroundTexture);

        std::vector<int> shortestPath = dijkstra(g, 0);
        float speed = 200.0f;

        for (int i = 1; i < shortestPath.size(); ++i) {
            int targetVertex = shortestPath[i];
            sf::Vector2f targetPosition = g.verticesInfo[targetVertex].position;

            // Atualize a posição do personagem em direção ao próximo vértice
            sf::Vector2f direction = targetPosition - characterPosition;
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

                character.setPosition(characterPosition);
                window.draw(character);
                window.display();

                sf::sleep(sf::milliseconds(20));  // Introduce a delay for smooth movement

                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }
            }

            characterPosition = targetPosition;  // Garante que o personagem esteja exatamente no destino
        }

        std::cout << "Chegou ao destino!" << std::endl;
    }
}
