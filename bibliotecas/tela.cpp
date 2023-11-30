#include <SFML/Graphics.hpp>
#include "mapa.hpp"
#include "tela.hpp"
#include <iostream>
#include "guarda_nivel.hpp"

namespace tl{
    void jogo_salvo(sf::RenderWindow &window){
        
            sf::Font font;\
            if (!font.loadFromFile("assets/arial_narrow_7.ttf"))
            {
                //erro...
            }
            sf::Texture backgroundTexture;
                    if (!backgroundTexture.loadFromFile("assets/fundo.png")){
                        //erro...
                    }

                    sf::Sprite background(backgroundTexture);

            window.draw(background);

            sf::Text text("Ha um jogo salvo, \ndeseja continuar de \nonde parou?", font);
            text.setPosition(210, 125);
            window.draw(text);

            /* Desenhar sim*/
            text.setCharacterSize(45);
            text.setFillColor(sf::Color::Green);
            text.setString("[S] sim");
            text.setPosition(220, 240);
            window.draw(text);

            /* Desenhar não*/
            text.setCharacterSize(45);
            text.setFillColor(sf::Color::Red);
            text.setString("[N] nao");
            text.setPosition(220, 300);
            window.draw(text);

            window.display();
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
                    window.draw(botaoNivel[i]);
                }

                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed||(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                        window.close();
                }
                
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        posicaoMouse = sf::Mouse::getPosition(window);
                        scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                        mouse.setPosition(scaledMousePosition);
                        for (int i = 0; i < 4; i++) {
                            if(mouse.getGlobalBounds().intersects(botaoNivel[i].getGlobalBounds()) && elapsed.asSeconds() >= 0.01f){
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
                    }
                }
                //window.draw(mouse);
                window.display();
    }

    void tela_manual(sf::RenderWindow &window, int i){
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
        text.setPosition(160, 370);
        window.draw(text);

        text.setString("[X] - RESETAR NÍIEL");
        text.setPosition(195, 405);
        window.draw(text);


        if(i==1){
            button.setPosition(205, 492);
            button.setSize(sf::Vector2f(190, 35));
            window.draw(button);

            text.setString("VOLTAR");
            text.setPosition(245, 500);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }
        else if(i==2){
            button.setPosition(200, 442);
            button.setSize(sf::Vector2f(220, 35));
            window.draw(button);

            text.setString("VOLTAR PARA O JOGO");
            text.setPosition(215, 450);
            text.setFillColor(sf::Color::Black);
            window.draw(text);

            button.setPosition(190, 492);
            button.setSize(sf::Vector2f(260, 35));
            window.draw(button);

            text.setString("VOLTAR PARA O MENU INICIAL");
            text.setPosition(210, 500);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }

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

                    sf::RectangleShape PrimeiroBotao;
                    PrimeiroBotao.setPosition(200, 500);
                    PrimeiroBotao.setSize(sf::Vector2f(200, 60));
                    PrimeiroBotao.setFillColor(sf::Color::Transparent);

                    sf::RectangleShape SegundoBotao;
                    SegundoBotao.setPosition(200, 450);
                    SegundoBotao.setSize(sf::Vector2f(200, 60));
                    SegundoBotao.setFillColor(sf::Color::Transparent);

                    window.draw(background);
                    tela_manual(window, i);

                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed||(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                            window.close();
                    }
                    
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Time elapsed = clock.getElapsedTime();
                            posicaoMouse = sf::Mouse::getPosition(window);
                            scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                            mouse.setPosition(scaledMousePosition);
                            if (mouse.getGlobalBounds().intersects(PrimeiroBotao.getGlobalBounds())) {
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                    if(elapsed.asSeconds() >= 0.01f){
                                        currentScreen = TITLE;
                                        clock.restart();
                                    }
                                }
                            }
                            else if(i==2){
                                if (mouse.getGlobalBounds().intersects(SegundoBotao.getGlobalBounds())) {
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                    if(elapsed.asSeconds() >= 0.01f){
                                        currentScreen = GAMEPLAY;
                                        clock.restart();
                                    }
                                }
                            }
                            }
                        }
                    }
                    window.draw(PrimeiroBotao);
                    if(i==2)
                        window.draw(SegundoBotao);
                    //window.draw(mouse);
                    window.display();
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
        text.setPosition(200, 160);
        window.draw(text);

        text.setString("PAULO VITOR (FRIGOBAR)");
        text.setPosition(220, 195);
        window.draw(text);

        text.setString("EMANUEL ALARCON (ISCO)");
        text.setPosition(225, 230);
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

                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed||(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                            window.close();
                    }
                    
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Time elapsed = clock.getElapsedTime();
                            posicaoMouse = sf::Mouse::getPosition(window);
                            scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                            mouse.setPosition(scaledMousePosition);
                            if (mouse.getGlobalBounds().intersects(botaoNivel.getGlobalBounds())) {
                                sf::Time elapsed = clock.getElapsedTime();
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentScreen == CREDITO && elapsed.asSeconds() >= 0.01f) {
                                        currentScreen = TITLE;
                                        clock.restart();
                                }
                            }
                        }
                    }
                    window.draw(botaoNivel);
                    //window.draw(mouse);
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
}