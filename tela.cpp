#include <SFML/Graphics.hpp>
#include "mapa.hpp"
#include "tela.hpp"
#include <iostream>

#define QTD_QUADRADOS 12 // Quantidade de quadrados na tela

void atualiza_posicao_jogador(int& x, int& y, MAPA mapa){
            for(int i=0; i<QTD_QUADRADOS; i++){
                    for(int j=0; j<QTD_QUADRADOS; j++){
                        if(mapa.mapa[i][j]=='P'){
                        y=i; x=j;
                        }
                    }
            }
}

void tela_titulo(sf::RenderWindow &window){
    sf::Font font;\
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))
    {
        //erro...
    }
    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    
    /* Desenhar "SOKOBAN"*/
    text.setString("SOKOBAN");
    text.setPosition(250, 125);
    window.draw(text);
    
    text.setString("GASPARZINHO");
    text.setPosition(190, 170);
    text.setCharacterSize(50);
    window.draw(text);

    sf::RectangleShape button;
    button.setSize(sf::Vector2f(260, 40));
    button.setFillColor(sf::Color(211,211,211)); 
    
    
    button.setPosition(170, 300);
    window.draw(button);
    text.setString("JOGAR");
    text.setPosition(270, 312);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    window.draw(text);
    
    
    button.setPosition(170, 360);
    window.draw(button);
    text.setString("INSTRUCOES");
    text.setPosition(260, 372);
    window.draw(text);
    
    
    button.setPosition(170, 420);
    window.draw(button);
    text.setString("CREDITOS");
    text.setPosition(270, 432);
    window.draw(text);
    
    
    button.setPosition(170, 480);
    window.draw(button);
    text.setString("ESCOLHER NIVEL");
    text.setPosition(235, 492);
    window.draw(text);
    
    
    text.setString("Para sair do jogo pressione ESC");
    text.setPosition(161, 550);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void titulo(sf::RenderWindow &window, GameScreen &currentScreen, sf::Clock &clock){
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/fundo.png")){
            //erro...
        }

        sf::Sprite background(backgroundTexture);
        sf::RectangleShape mouse(sf::Vector2f(15, 15));
        sf::RectangleShape botaoNivel[4];
        for(int i=0; i<4; i++){
            botaoNivel[i].setPosition(200, 300 + 60 * i);
            botaoNivel[i].setSize(sf::Vector2f(200, 50));
            botaoNivel[i].setFillColor(sf::Color::Transparent);
        }
            sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
            double p = window.getSize().x / 600.0;
            sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
            mouse.setPosition(scaledMousePosition);
            window.draw(background);
        tela_titulo(window);

        sf::Time elapsed = clock.getElapsedTime();
            for(int i=0; i<4; i++){
                if(mouse.getGlobalBounds().intersects(botaoNivel[i].getGlobalBounds()) && elapsed.asSeconds() >= 1.0f){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                        clock.restart();
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
            
            window.draw(mouse);
            window.display();
            }
}

void tela_manual(sf::RenderWindow &window){
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(220, 40));
    button.setFillColor(sf::Color(211,211,211));

    sf::Font font;
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))
    {
        //erro...
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);

    button.setPosition(190, 90);
    window.draw(button);
    text.setString("COMO JOGAR:");
    text.setPosition(222, 100);
    window.draw(text);

    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString("[W] - CIMA");
    text.setPosition(248, 160);
    window.draw(text);

    text.setString("[A] - ESQUERDA");
    text.setPosition(225, 195);
    window.draw(text);

    text.setString("[S] - BAIXO");
    text.setPosition(245, 230);
    window.draw(text);

    text.setString("[D] - DIREITA");
    text.setPosition(230, 265);
    window.draw(text);

    text.setString("[M] - MENU");
    text.setPosition(246, 300);
    window.draw(text);

    text.setString("[Z] - VOLTAR JOGADA");
    text.setPosition(190, 335);
    window.draw(text);

    text.setString("[C] - DESFAZER VOLTA DE JOGADA");
    text.setPosition(115, 370);
    window.draw(text);

    text.setString("[X] - RESETAR NÍVEL");
    text.setPosition(195, 405);
    window.draw(text);

    button.setPosition(205, 492);
    button.setSize(sf::Vector2f(190, 35));
    window.draw(button);
    text.setString("VOLTAR");
    text.setPosition(245, 500);
    text.setFillColor(sf::Color::Black);
    window.draw(text);

    text.setString("Para sair do jogo pressione ESC");
    text.setPosition(161, 550);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void Manual(sf::RenderWindow &window, int i, GameScreen &currentScreen, sf::Clock &clock){
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png")){
                    //erro...
                }

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
                tela_manual(window);

                if (mouse.getGlobalBounds().intersects(buttonBounds.getGlobalBounds())) {
                    sf::Time elapsed = clock.getElapsedTime();
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if(i==1 && currentScreen == MANUAL1 && elapsed.asSeconds() >= 1.0f){
                            currentScreen = TITLE;
                            clock.restart();
                        }
                        else if(i==2 && currentScreen == MANUAL2 && elapsed.asSeconds() >= 1.0f)
                            currentScreen = MENU;
                            clock.restart();
                    }
                }
                window.draw(buttonBounds);
                window.draw(mouse);
                window.display();
}

void Menu(sf::RenderWindow &window, GameScreen &currentScreen, sf::Clock &clock){
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
                                sf::Time elapsed = clock.getElapsedTime();
                                for(int i=0; i<3; i++){
                                    if(botaoNivel[i].getGlobalBounds().intersects(mouse.getGlobalBounds())&& elapsed.asSeconds() >= 1.0f){
                                        if(i==0)
                                            currentScreen = GAMEPLAY;
                                        if(i==1)
                                            currentScreen = MANUAL2;
                                        if(i==2)
                                            currentScreen = TITLE;

                                        clock.restart();
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

                            clock.restart();
                        }
                    }

                    window.clear();
                    window.draw(background);
                    window.display();
                }
}

void tela_creditos(sf::RenderWindow &window){
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(220, 40));
    button.setFillColor(sf::Color(211,211,211));

    sf::Font font;
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))
    {
        //erro...
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);

    button.setPosition(190, 90);
    window.draw(button);
    text.setString("PARTICIPANTES");
    text.setPosition(222, 100);
    window.draw(text);

    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString("AUGUSTO NASCIMENTO (AMBULANCIA)");
    text.setPosition(248, 160);
    window.draw(text);

    text.setString("PAULO VITOR (FRIGOBAR)");
    text.setPosition(225, 195);
    window.draw(text);

    text.setString("EMANUEL ALARCON (ISCO)");
    text.setPosition(245, 230);
    window.draw(text);

    button.setPosition(205, 492);
    button.setSize(sf::Vector2f(190, 35));
    window.draw(button);
    text.setString("VOLTAR");
    text.setPosition(245, 500);
    text.setFillColor(sf::Color::Black);
    window.draw(text);

    text.setString("Para sair do jogo pressione ESC");
    text.setPosition(161, 550);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}
void Creditos(sf::RenderWindow &window, GameScreen &currentScreen, sf::Clock &clock){
                sf::Texture backgroundTexture;
                if (!backgroundTexture.loadFromFile("assets/fundo.png"))
                {
                    // erro...
                }

                sf::Sprite background(backgroundTexture);

                sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                double p = window.getSize().x / 600.0;
                sf::Vector2f scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                
                sf::RectangleShape mouse(sf::Vector2f(15, 15));
                mouse.setPosition(scaledMousePosition);

                sf::RectangleShape botaoNivel;
                botaoNivel.setPosition(200, 500);
                botaoNivel.setSize(sf::Vector2f(200, 60));
                botaoNivel.setFillColor(sf::Color::Transparent);

                window.draw(background);
                tela_creditos(window);

                if (mouse.getGlobalBounds().intersects(botaoNivel.getGlobalBounds())) {
                    sf::Time elapsed = clock.getElapsedTime();
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentScreen == CREDITO && elapsed.asSeconds() >= 1.0f) {
                            currentScreen = TITLE;
                            clock.restart();
                    }
                }
                window.draw(botaoNivel);
                window.draw(mouse);
                window.display();
}

void legenda_gameplay(sf::RenderWindow &window, GameScreen &currentScreen, sf::Clock &clock){
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(200, 60));
    button.setFillColor(sf::Color(211,211,211));

    sf::Font font;
    if (!font.loadFromFile("assets/arial_narrow_7.ttf"))
    {
        //erro...
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);

    button.setPosition(200, 500);
    window.draw(button);
    text.setString("PAUSA");
    text.setPosition(250, 510);
    window.draw(text);
}
