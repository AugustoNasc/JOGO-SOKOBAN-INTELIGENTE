#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "jogo.hpp"
#include "bibliotecas/voltajogada.hpp"

#define QTD_QUADRADOS 12 
#define LARGURA 600
#define DIMENSAO LARGURA/QTD_QUADRADOS

int gX=0, gY=0;

MAPA mapa;

int main()
{
    sf::RenderWindow window(sf::VideoMode(LARGURA, LARGURA), "Gasparzinho");
    window.setKeyRepeatEnabled(false); // Desativa a repetição de teclas
    GameScreen currentScreen = TITLE;

    direcaoPersonagem sentido = FRENTE;
    int level=1;

    Quadrado *imagens;
    imagens = new Quadrado[10];

    Quadrado *fundo;
    fundo = new Quadrado[13];

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/fundo.png"))
        return -1;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    char endereco[50];

    mapa_declarar_imagens_usadas(&imagens);
    mapa_declarar_background_fundo(&fundo);

    mapa=novo_mapa(level, gX, gY, endereco);

    bool mapas_acessados[13];
    atualiza_niveis_acessados(mapas_acessados);

    int voltando=0;
    int verticeAtualPersonagem=0;
    
    window.setFramerateLimit(144);
    sf::Clock clock; //marcar tempo, para não clicar instantaneamente assim que se troca de tela

    int forca=3; //vai até o ivel 3

    
    if(ha_jogo_salvo()){
        tl::jogo_salvo(window);

    // Aguarda a entrada do usuário
    while (true)
    {
        sf::Event continueEvent;
        while (window.pollEvent(continueEvent))
        {
            if(continueEvent.type == sf::Event::Closed){
                window.close();
                return 0;
            }
            if (continueEvent.type == sf::Event::KeyPressed)
            {
                if (continueEvent.key.code == sf::Keyboard::N)
                {
                    // Apaga arquivo
                    FILE *file = fopen("jogadas/niveis_salvos.txt", "w");
                    if (file != NULL) {
                        fclose(file);
                    }
                    atualiza_niveis_acessados(mapas_acessados);
                    vtj::apagar_jogadas(level);
                    while(window.isOpen())
                        carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, sentido, imagens, fundo, verticeAtualPersonagem, forca);
                }
                else if (continueEvent.key.code == sf::Keyboard::S)
                {
                    verticeAtualPersonagem=ultimo_nivel_desbloqueado()-1;
                    if(verticeAtualPersonagem+1<=6 && verticeAtualPersonagem+1>=4) forca=6;
                    else if(verticeAtualPersonagem+1<=9 && verticeAtualPersonagem+1>=7) forca=9;
                    else if(verticeAtualPersonagem+1<=11 && verticeAtualPersonagem+1>=9) forca=11;
                    else if(verticeAtualPersonagem+1<=13 && verticeAtualPersonagem+1>=12) forca=13;

                    std::cout<<forca<<std::endl;

                    while(window.isOpen())
                        carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, sentido, imagens, fundo, verticeAtualPersonagem, forca);
                }
                break;
            }
        }
        if (!window.isOpen())
            break;
    }
    }
    else{
        while(window.isOpen())
            carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, sentido, imagens, fundo, verticeAtualPersonagem, forca);
    }


    delete[] imagens;
    delete[] fundo;

    return 0;
}