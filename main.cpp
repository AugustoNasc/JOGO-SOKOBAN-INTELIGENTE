#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "mapa.hpp"
#include <string>
#include <string.h>
#include <iostream>
#include "movimentos.hpp"
#include "voltajogada.hpp"
#include "guarda_nivel.hpp"
#include "tela.hpp"
#include "grafo.hpp"

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
    int level=1, maximo=1, Ultimo=0;

    Quadrado *imagens;
    imagens = new Quadrado[6];

    Quadrado *fundo;
    fundo = new Quadrado[13];

    sf::Vector2i posicaoMouse = sf::Mouse::getPosition();

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
                window.draw(backgroundSprite);

                // Desenhar elementos específicos da tela de parabéns
                
                    sf::Font font;
                    if (!font.loadFromFile("font.ttf"))
                        return -1;

                    sf::Text congratulationsText("PARABÉNS!!", font, 55);
                    congratulationsText.setFillColor(sf::Color::White);
                    congratulationsText.setPosition(120, 170);

                    window.draw(congratulationsText);
                

                if (!Ultimo) {
                    sf::RectangleShape continueButton(sf::Vector2f(260, 40));
                    sf::Color lightGray(211, 211, 211);
                    continueButton.setFillColor(lightGray);

                    continueButton.setPosition(173, 300);

                    window.draw(continueButton);

                    sf::Text continueText("CONTINUAR [ENTER]", font, 20);
                    continueText.setFillColor(sf::Color::Black);
                    continueText.setPosition(198, 312);

                    window.draw(continueText);
                }

                {
                    sf::RectangleShape menuButton(sf::Vector2f(260, 40));
                    sf::Color lightGray(211, 211, 211);
                    menuButton.setFillColor(lightGray);
                    menuButton.setPosition(172, 360);

                    window.draw(menuButton);

                    sf::Text menuText("MENU PRINCIPAL [Q]", font, 20);
                    menuText.setFillColor(sf::Color::Black);
                    menuText.setPosition(202, 372);

                    window.draw(menuText);
                }

            }
            break;

            default:
            break;
        }

        //window.display();
        //window.clear(sf::Color::White);

        window.display();

        if(finalizou_mapa(mapa)){
        
            //currentScreen = PARABENS;
            vtj::apagar_jogadas(level);
            if(level!=13){
                level++;
                Ultimo=0;
            }
            else{
                level=1;
                Ultimo=1;
            }
                salvar_nivel(level);
                sprintf(endereco, "mapastxt/mapa%d.txt", level);
                arquivo = fopen(endereco, "rt");
                fread(mapa.mapa, sizeof(char), 12*13, arquivo);
                declarar_posicoes_de_encaixe(&mapa);
            //PlaySound(conseguiu);
            //SetSoundVolume(conseguiu, 0.3);
            mv::atualiza_posicao_jogador(gX, gY, mapa);
            sentido=FRENTE;
    
                //PlayMusicStream(jogando);
    }

        
}


    delete[] imagens;
    delete[] fundo;

    return 0;
}
