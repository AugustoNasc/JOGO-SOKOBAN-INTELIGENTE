#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bibliotecas/mapa.hpp"
#include <string>
#include <string.h>
#include <iostream>
#include "bibliotecas/movimentos.hpp"
#include "bibliotecas/voltajogada.hpp"
#include "bibliotecas/guarda_nivel.hpp"
#include "bibliotecas/tela.hpp"
#include "bibliotecas/grafo.hpp"

#define QTD_QUADRADOS 12 
#define LARGURA 600
#define DIMENSAO LARGURA/QTD_QUADRADOS

int gX=0, gY=0;

MAPA mapa;

int main()
{
    FILE *arquivo;
    sf::RenderWindow window(sf::VideoMode(LARGURA, LARGURA), "Gasparzinho");
    window.setKeyRepeatEnabled(false); // Desativa a repetição de teclas
    GameScreen currentScreen = TITLE;

    sf::Music jogando, abertura;
    sf::SoundBuffer conseguiuBuffer;
    sf::Sound conseguiu;

    direcaoPersonagem sentido = FRENTE;
    int level=1;

    Quadrado *imagens;
    imagens = new Quadrado[6];

    Quadrado *fundo;
    fundo = new Quadrado[13];

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/fundo.png"))
        return -1;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    char endereco[50];
    sprintf(endereco, "mapastxt/mapa%d.txt", level);
    arquivo = fopen(endereco, "rt");
    fread(mapa.mapa, sizeof(char), 12*13, arquivo);
    declarar_posicoes_de_encaixe(&mapa);
    mv::atualiza_posicao_jogador(gX, gY, mapa);

    mapa_declarar_imagens_usadas(&imagens);
    mapa_background_fundo(&fundo);

    int voltando=0;
    window.setFramerateLimit(144);
    sf::Clock clock; //marcar tempo, para não clicar instantaneamente assim que se troca de tela
    
    while (window.isOpen()) {
        

        window.clear();
        switch (currentScreen) {
            case TITLE: {
                tl::titulo(window, currentScreen, clock);
            }
            
            break;

            case MENU: {
                tl::Menu(window, currentScreen, clock);
            }
            break;

            case MANUAL1: {
                tl::Manual(window, 1, currentScreen, clock);
            }
            break;

            case MANUAL2:{
                tl::Manual(window, 2, currentScreen, clock);
            }
            break;

            case CREDITO:{
                tl::Creditos(window, currentScreen, clock);
            }
            break;

            case ESCOLHER_NIVEL:{

                Graph g;

                grafo_do_jogo(g);

                desenhaGrafo_e_direcionaMapa(g, window, mapa, currentScreen, gX, gY, level);
                
            }
            break;

            case GAMEPLAY:{

                sf::Texture backgroundTexture;
                mapa_desenhando(sentido, mapa, imagens, fundo, level, window);

                sf::Sprite background(backgroundTexture);
                sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                double p = window.getSize().x / 600.0;
                sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition(scaledMousePosition);

                sf::RectangleShape botaoNivel;
                botaoNivel.setPosition(200, 500);
                botaoNivel.setSize(sf::Vector2f(200, 60));

                tl::legenda_gameplay(window, currentScreen, clock);

                // Verificar a colisão
                sf::Time elapsed = clock.getElapsedTime();
                if (botaoNivel.getGlobalBounds().intersects(mouse.getGlobalBounds())&& elapsed.asSeconds() >= 1.0f) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        // Ação quando o botão esquerdo do mouse é liberado
                        currentScreen = MANUAL2;
                    }
                    clock.restart();
                }
                else{
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                        window.close();

                        if(event.type == sf::Event::KeyPressed){
                        
                            mv::atualiza_posicao_jogador(gX, gY, mapa);
                            mv::comando_por_tecla(event, sentido, voltando, gX, gY, mapa, level, clock);

                        }
                    }
                }
            }
            break;

            case PARABENS:{
               

            }
            break;

            default:
            break;
        }

        window.display();

        if(finalizou_mapa(mapa)){
        
            //currentScreen = PARABENS;
            vtj::apagar_jogadas(level);
            if(level!=13){
                level++;
            }
            else{
                level=1;
            }
                salvar_nivel(level);
                sprintf(endereco, "mapastxt/mapa%d.txt", level);
                arquivo = fopen(endereco, "rt");
                fread(mapa.mapa, sizeof(char), 12*13, arquivo);
                declarar_posicoes_de_encaixe(&mapa);
            mv::atualiza_posicao_jogador(gX, gY, mapa);
            sentido=FRENTE;
    
    }

        
}


    delete[] imagens;
    delete[] fundo;

    return 0;
}
