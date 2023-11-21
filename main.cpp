#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "mapa.hpp"
#include <string>
#include <string.h>
#include <iostream>
#include "movimentos.hpp"
#include "voltajogada.hpp"
#include "guarda_nivel.hpp"

#define QTD_QUADRADOS 12 
#define LARGURA 600
#define DIMENSAO LARGURA/QTD_QUADRADOS
#define POSICAO for(int i=0; i<QTD_QUADRADOS; i++){\
                    for(int j=0; j<QTD_QUADRADOS; j++){\
\
                        if(mapa.mapa[i][j]=='P'){\
                            gY=i; gX=j;\
                        }\
\
                    }\
                }

#define TELA_TITULO\
    sf::Font font;\
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))\
    {\
        std::cout<<"tristefim"<<std::endl;\
    }\
    \
    sf::Text text;\
    text.setFont(font);\
    text.setCharacterSize(36);\
    text.setFillColor(sf::Color::White);\
    \
    /* Desenhar "SOKOBAN"*/\
    text.setString("SOKOBAN");\
    text.setPosition(250, 125);\
    window.draw(text);\
    \
    text.setString("GASPARZINHO");\
    text.setPosition(190, 170);\
    text.setCharacterSize(50);\
    window.draw(text);\
\
    sf::RectangleShape button;\
    button.setSize(sf::Vector2f(260, 40));\
    button.setFillColor(sf::Color(211,211,211)); \
    \
    \
    button.setPosition(170, 300);\
    window.draw(button);\
    text.setString("JOGAR");\
    text.setPosition(270, 312);\
    text.setCharacterSize(20);\
    text.setFillColor(sf::Color::Black);\
    window.draw(text);\
    \
    \
    button.setPosition(170, 360);\
    window.draw(button);\
    text.setString("INSTRUCOES");\
    text.setPosition(260, 372);\
    window.draw(text);\
    \
    \
    button.setPosition(170, 420);\
    window.draw(button);\
    text.setString("CREDITOS");\
    text.setPosition(270, 432);\
    window.draw(text);\
    \
    \
    button.setPosition(170, 480);\
    window.draw(button);\
    text.setString("ESCOLHER NIVEL");\
    text.setPosition(235, 492);\
    window.draw(text);\
    \
    \
    text.setString("Para sair do jogo pressione ESC");\
    text.setPosition(161, 550);\
    text.setFillColor(sf::Color::White);\
    window.draw(text);\

#define TELA_MENU1\
    sf::RectangleShape button;\
    button.setSize(sf::Vector2f(220, 40));\
    button.setFillColor(sf::Color(211,211,211));\
\
    sf::Font font;\
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))\
    {\
    }\
\
    sf::Text text;\
    text.setFont(font);\
    text.setCharacterSize(25);\
    text.setFillColor(sf::Color::Black);\
\
    button.setPosition(190, 90);\
    window.draw(button);\
    text.setString("COMO JOGAR:");\
    text.setPosition(222, 100);\
    window.draw(text);\
\
    text.setCharacterSize(20);\
    text.setFillColor(sf::Color::White);\
    text.setString("[W] - CIMA");\
    text.setPosition(248, 160);\
    window.draw(text);\
\
    text.setString("[A] - ESQUERDA");\
    text.setPosition(225, 195);\
    window.draw(text);\
\
    text.setString("[S] - BAIXO");\
    text.setPosition(245, 230);\
    window.draw(text);\
\
    text.setString("[D] - DIREITA");\
    text.setPosition(230, 265);\
    window.draw(text);\
\
    text.setString("[M] - MENU");\
    text.setPosition(246, 300);\
    window.draw(text);\
\
    text.setString("[Z] - VOLTAR JOGADA");\
    text.setPosition(190, 335);\
    window.draw(text);\
\
    text.setString("[C] - DESFAZER VOLTA DE JOGADA");\
    text.setPosition(115, 370);\
    window.draw(text);\
\
    text.setString("[X] - RESETAR NÍVEL");\
    text.setPosition(195, 405);\
    window.draw(text);\
\
    button.setPosition(205, 492);\
    button.setSize(sf::Vector2f(190, 35));\
    window.draw(button);\
    text.setString("VOLTAR");\
    text.setPosition(245, 500);\
    text.setFillColor(sf::Color::Black);\
    window.draw(text);\
\
    text.setString("Para sair do jogo pressione ESC");\
    text.setPosition(161, 550);\
    text.setFillColor(sf::Color::White);\
    window.draw(text);


int gX, gY;

typedef enum GameScreen { TITLE = 0, MENU, MANUAL1, MANUAL2, ESCOLHER_NIVEL, CREDITO, GAMEPLAY, PARABENS } GameScreen;

MAPA mapa;


int main()
{
    FILE *arquivo;
    sf::RenderWindow window(sf::VideoMode(LARGURA, LARGURA), "Gasparzinho");
    GameScreen currentScreen = TITLE;

    sf::Music jogando, abertura;
    sf::SoundBuffer conseguiuBuffer;
    sf::Sound conseguiu;
    
    /*if (!conseguiuBuffer.loadFromFile("assets/musica/fim_fase.mp3"))
        return -1;

    if (!jogando.openFromFile("assets/musica/menumsc.mp3"))
        return -1;

    if (!abertura.openFromFile("assets/musica/suspira.mp3"))
        return -1;*/

    int flag=0;
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
    mapa_especial(&mapa);
    POSICAO;

    mapa_declararpng(&imagens);
    mapa_fundo(&fundo);

    int voltando=0;
    window.setFramerateLimit(144);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        switch (currentScreen) {
            case TITLE: {

                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                    return EXIT_FAILURE;

                sf::Sprite background(backgroundTexture);

                sf::RectangleShape mouse(sf::Vector2f(15, 15));

                sf::RectangleShape botaoNivel[4];
                for(int i=0; i<4; i++){
                    botaoNivel[i].setPosition(200, 300 + 60 * i);
                    botaoNivel[i].setSize(sf::Vector2f(200, 50));
                    botaoNivel[i].setFillColor(sf::Color::Transparent);
                }

                //while (window.isOpen())
                //{
                    //sf::Event event;
                    //while (window.pollEvent(event))
                    //{
                       // if (event.type == sf::Event::Closed)
                     //       window.close();
                    //}

                    sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                    double p = window.getSize().x / 600.0;
                    sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                    mouse.setPosition(scaledMousePosition);

                    window.draw(background);

                TELA_TITULO;
                    for(int i=0; i<4; i++){
                        if(mouse.getGlobalBounds().intersects(botaoNivel[i].getGlobalBounds())){
                            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                                if(i==0)
                                    currentScreen = GAMEPLAY;
                                if(i==1)
                                    currentScreen = MANUAL1;
                                if(i==2)
                                    currentScreen = CREDITO;
                                if(i==3)
                                    currentScreen = ESCOLHER_NIVEL;
                            }
                        }
                        window.draw(botaoNivel[i]);
                    }

                    window.draw(mouse);
                    window.display();
                //}
            }
            
            break;

            case MENU: {
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                {
                    // erro...
                }

                sf::Sprite background(backgroundTexture);
                background.setScale((float)window.getSize().x / 600, (float)window.getSize().y / 600);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition();
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition((float)posicaoMouse.x, (float)posicaoMouse.y);

                sf::RectangleShape botaoNivel[3];

                for(int i=0; i<3; i++){
                    botaoNivel[i].setPosition(200, 322+60*i);
                    botaoNivel[i].setSize(sf::Vector2f(200, 60));
                }

                while (window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();

                        if (event.type == sf::Event::MouseButtonReleased)
                        {
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                for(int i=0; i<3; i++){
                                    if(botaoNivel[i].getGlobalBounds().intersects(mouse.getGlobalBounds())){
                                        if(i==0)
                                            currentScreen = GAMEPLAY;
                                        if(i==1)
                                            currentScreen = MANUAL2;
                                        if(i==2)
                                            currentScreen = TITLE;
                                    }
                                }
                            }
                        }

                        if (event.type == sf::Event::KeyPressed)
                        {
                            if (event.key.code == sf::Keyboard::Enter)
                            {
                                currentScreen = GAMEPLAY;
                            }

                            if (event.key.code == sf::Keyboard::I)
                            {
                                currentScreen = MANUAL2;
                            }

                            if (event.key.code == sf::Keyboard::Q)
                            {
                                currentScreen = TITLE;
                            }
                        }
                    }

                    window.clear();
                    window.draw(background);
                    window.display();
                }
            }
            break;

            case MANUAL1: {
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                    return EXIT_FAILURE;

                sf::Sprite background(backgroundTexture);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                double p = window.getSize().x / 600.0;
                sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition(scaledMousePosition);

                sf::RectangleShape buttonBounds;
                buttonBounds.setPosition(200, 500);
                buttonBounds.setSize(sf::Vector2f(200, 60));
                buttonBounds.setFillColor(sf::Color::Transparent);

                window.draw(background);
                TELA_MENU1;

                if (mouse.getGlobalBounds().intersects(buttonBounds.getGlobalBounds())) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        currentScreen = TITLE;
                    }
                }
                window.draw(buttonBounds);
                window.draw(mouse);
                window.display();

            }

            break;

            case MANUAL2:{
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                    return EXIT_FAILURE;

                sf::Sprite background(backgroundTexture);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                double p = window.getSize().x / 600.0;
                sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition(scaledMousePosition);

                sf::RectangleShape buttonBounds;
                buttonBounds.setPosition(200, 500);
                buttonBounds.setSize(sf::Vector2f(200, 60));
                buttonBounds.setFillColor(sf::Color::Transparent);

                window.draw(background);
                TELA_MENU1;

                if (mouse.getGlobalBounds().intersects(buttonBounds.getGlobalBounds())) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        currentScreen = MENU;
                    }
                }
                window.draw(buttonBounds);
                window.draw(mouse);
                window.display();

            }
            break;

            case CREDITO:{
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                {
                    // erro...
                }

                sf::Sprite background(backgroundTexture);
                background.setScale((float)window.getSize().x / 600, (float)window.getSize().y / 600);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition();
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition((float)posicaoMouse.x, (float)posicaoMouse.y);

                sf::RectangleShape botaoNivel;
                botaoNivel.setPosition(200, 500);
                botaoNivel.setSize(sf::Vector2f(200, 60));

                while (window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();

                        if (event.type == sf::Event::MouseButtonReleased)
                        {
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                if(botaoNivel.getGlobalBounds().intersects(mouse.getGlobalBounds())){
                                    currentScreen = TITLE;
                                }
                            }
                        }

                        if (event.type == sf::Event::KeyPressed)
                        {
                            if (event.key.code == sf::Keyboard::Q)
                            {
                                currentScreen = TITLE;
                            }
                        }
                    }

                    window.clear();
                    window.draw(background);
                    window.display();
                }
            }
            break;

            case ESCOLHER_NIVEL:{
                int maximo = guarda_ler_nivel();

                sf::Texture texture;
                if (!texture.loadFromFile("assets/fundo.png"))
                {
                    // erro...
                }
                sf::Sprite sprite(texture);
                sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
                sprite.setPosition(0, 0);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition();
                double p = sf::VideoMode::getDesktopMode().width / 600.0;
                sf::Mouse::setPosition(sf::Vector2i(posicaoMouse.x / p, posicaoMouse.y / p));

                sf::RectangleShape mouse(sf::Vector2f(6, 6));
                mouse.setPosition((float)posicaoMouse.x, (float)posicaoMouse.y);

                std::vector<sf::RectangleShape> botaoNivel(maximo);
                for(int i = 0; i < maximo; i++)
                {
                    botaoNivel[i].setPosition(280, 80 + 35 * (i + 1));
                    botaoNivel[i].setSize(sf::Vector2f(50, 20));
                }

                for(int i = 0; i < maximo; i++)
                {
                    if(botaoNivel[i].getGlobalBounds().contains(mouse.getPosition()))
                    {
                        char endereco[50];
                        sprintf(endereco, "%d", i + 1);
                        // DrawText(endereco, 300, 90 + 40 * (i + 1), 20, sf::Color::Black);

                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            int level = i + 1;
                            // mapa = mapa_rezetar(level);
                            // POSICAO;
                            // mapa_especial(&mapa);
                            // currentScreen = GAMEPLAY;
                        }
                    }

                    sf::RectangleShape botaoNivel2(sf::Vector2f(200, 50));
                    botaoNivel2.setPosition(400, 550);

                    if(botaoNivel2.getGlobalBounds().contains(mouse.getPosition()))
                    {
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            // currentScreen = TITLE;
                        }
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    // currentScreen = TITLE;
                }
            }
            break;

            case GAMEPLAY:{

                window.clear();
            // Obter a posição do mouse
            sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);

            // Criar o retângulo do mouse
            sf::RectangleShape mouse(sf::Vector2f(15, 15));
            mouse.setPosition((float)posicaoMouse.x, (float)posicaoMouse.y);

            // Criar o botão
            sf::RectangleShape botaoNivel(sf::Vector2f(200, 60));
            botaoNivel.setPosition(200, 500);

            // Verificar a colisão
            if (botaoNivel.getGlobalBounds().intersects(mouse.getGlobalBounds())) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Ação quando o botão esquerdo do mouse é liberado
                    currentScreen = MENU;
                }
            }

            if(event.type == sf::Event::KeyPressed){

                if((event.key.code==sf::Keyboard::A)||(event.key.code==sf::Keyboard::Left)){ 
                        flag=1; 
                        voltando=0;
                        movimentos_move(&gX, &gY, flag, &mapa, level);
                    }

                    else if((event.key.code==sf::Keyboard::D)||(event.key.code==sf::Keyboard::Right)){ 
                        flag=2;
                        voltando=0;
                        movimentos_move(&gX, &gY, flag, &mapa, level);
                    }

                    else if((event.key.code==sf::Keyboard::S)||(event.key.code==sf::Keyboard::Down)){ 
                        flag=3;
                        voltando=0;
                        movimentos_move(&gX, &gY, flag, &mapa, level);
                    }

                    else if((event.key.code==sf::Keyboard::W)||(event.key.code==sf::Keyboard::Up)){ 
                        flag=4; 
                        voltando=0;
                        movimentos_move(&gX, &gY, flag, &mapa, level);
                    }

                    else if((event.key.code==sf::Keyboard::Z)){ 
                        voltando_jogada(&mapa, level, voltando);
                        voltando++;
                        //mapa.especial_atual[1][3]=1;
                        flag=0;
                        POSICAO;
                    }

                    else if((event.key.code==sf::Keyboard::C)){ 
                        if(voltando!=0){
                            adiantando_jogada(&mapa, level, voltando);
                            voltando--;
                            flag=0;
                            POSICAO;
                        }
                    }
                    else if((event.key.code==sf::Keyboard::X)){ 

                        mapa = mapa_rezetar(level);

                        mapa_especial(&mapa);

                        jogando.stop();

                        POSICAO;
                        flag=0;

                        jogando.play();
                    }
                    //provisorio, so para admins
                    /*else if((event.key.code==sf::Keyboard::P)&&level!=13){ 
                        apagar_jogadas(level);
                        level++;

                        sprintf(endereco, "mapastxt/mapa%d.txt", level);

                        arquivo = fopen(endereco, "rt");

                        fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                        mapa_especial(&mapa);

                        StopMusicStream(jogando);

                        POSICAO;
                        flag=0;

                        PlayMusicStream(jogando);
                    }

                    else if((event.key.code==sf::Keyboard::O)&&level!=1){ 
                        apagar_jogadas(level);
                        level--;

                        sprintf(endereco, "mapastxt/mapa%d.txt", level);

                        arquivo = fopen(endereco, "rt");

                        fread(mapa.mapa, sizeof(char), 12*13, arquivo);

                        mapa_especial(&mapa);

                        StopMusicStream(jogando);

                        POSICAO;
                        flag=0;

                        PlayMusicStream(jogando);
                    }*/

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
        
    }


    delete[] imagens;
    delete[] fundo;

    return 0;
}
