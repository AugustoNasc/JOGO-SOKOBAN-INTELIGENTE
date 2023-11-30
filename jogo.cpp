#include "jogo.hpp"     

void carrega_jogo(sf::RenderWindow &window, GameScreen &currentScreen, sf::Clock &clock, int &level, int &gX, 
                    int &gY, bool mapas_acessados[], MAPA &mapa, int *voltando, 
                    char endereco[],
                    direcaoPersonagem &sentido, Quadrado *imagens, Quadrado *fundo, int &verticeAtualPersonagem, int &forca){

        window.clear();
        switch (currentScreen) {
            case TITLE: {
                tl::titulo(window, currentScreen, clock);
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

                atualiza_niveis_acessados(mapas_acessados);

                desenhaGrafo_e_direcionaMapa(g, window, mapa, currentScreen, gX, gY, level, mapas_acessados, &verticeAtualPersonagem, forca);
                
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
                botaoNivel.setFillColor(sf::Color::Transparent);

                tl::legenda_gameplay(window, currentScreen, clock);


                sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed||(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                            window.close();

                        if(event.type == sf::Event::KeyPressed){
                    
                            mv::atualiza_posicao_jogador(gX, gY, mapa);
                            mv::comando_por_tecla(event, sentido,*voltando, gX, gY, mapa, level, clock, forca, window);
                        }
                    }
                    
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Time elapsed = clock.getElapsedTime();
                            posicaoMouse = sf::Mouse::getPosition(window);
                            scaledMousePosition = sf::Vector2f(posicaoMouse.x / p, posicaoMouse.y / p);
                            mouse.setPosition(scaledMousePosition);
                            if (mouse.getGlobalBounds().intersects(botaoNivel.getGlobalBounds())) {
                                sf::Time elapsed = clock.getElapsedTime();
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed.asSeconds() >= 0.01f) {
                                        currentScreen = MANUAL2;
                                        clock.restart();
                                }
                            }
                        }
                    }

                    window.draw(botaoNivel);
                    //window.display();
            }
            break;

            default:
            break;
        }

        window.display();

        if(finalizou_mapa(mapa)){

            if(level==3) forca=6;
            else if(level==6) forca=9;
            else if(level==8) forca=11;
            else if(level==11) forca=12;
            else if(level==12) forca=13;
        
            currentScreen = ESCOLHER_NIVEL;
            vtj::apagar_jogadas(level);
            salvar_nivel(level);
            verticeAtualPersonagem=level-1;
             if(level!=13){
                level++;
            }
            else{
                level=1;
            }
            mapa=novo_mapa(level, gX, gY, endereco);
            /* 
            atualiza_niveis_acessados(mapas_acessados);
            int destino=level;
            mv::anda_pelos_vertices(window, g, character, vertices, labels, edges, characterPosition, verticeAtualPersonagem, destino); */
                /*sprintf(endereco, "mapastxt/mapa%d.txt", level);
                arquivo = fopen(endereco, "rt");
                fread(mapa.mapa, sizeof(char), 12*13, arquivo);
                declarar_posicoes_de_encaixe(&mapa);
            mv::atualiza_posicao_jogador(gX, gY, mapa); */
            sentido=FRENTE;
    
    }
}

void toca_musica(std::string Musica){
    sf::Music music;
    std::string enderecoMusica = "assets/musica/" + Musica;
    if (!music.openFromFile(enderecoMusica))
        return ; // erro

    music.setLoop(true); // A música vai repetir

    music.play();
}