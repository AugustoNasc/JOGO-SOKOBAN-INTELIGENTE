#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "jogo.hpp"

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

    bool mapas_acessados[13];
    atualiza_mapas_acessados(mapas_acessados);

    int voltando=0;
    int verticeAtualPersonagem=0;
    
    window.setFramerateLimit(144);
    sf::Clock clock; //marcar tempo, para não clicar instantaneamente assim que se troca de tela

    
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
                    std::cout<<"apagado"<<std::endl;
                    if (file != NULL) {
                        fclose(file);
                    }
                    atualiza_mapas_acessados(mapas_acessados);
                    while(window.isOpen())
                        carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, arquivo, sentido, imagens, fundo, verticeAtualPersonagem);
                }
                else if (continueEvent.key.code == sf::Keyboard::S)
                {
                    verticeAtualPersonagem=ultimo_nivel_desbloqueado()-1;
                    while(window.isOpen())
                        carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, arquivo, sentido, imagens, fundo, verticeAtualPersonagem);
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
            carrega_jogo(window, currentScreen, clock, level, gX, gY, mapas_acessados, mapa, &voltando, endereco, arquivo, sentido, imagens, fundo, verticeAtualPersonagem);
    }


    delete[] imagens;
    delete[] fundo;

    return 0;
}