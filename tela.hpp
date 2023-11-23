#ifndef TELA_HPP
#define TELA_HPP

typedef enum GameScreen { TITLE = 0, MENU=1, MANUAL1=2, MANUAL2=3, ESCOLHER_NIVEL=4, CREDITO=5, GAMEPLAY=6, PARABENS=7 } GameScreen;
void atualiza_posicao_jogador(int&, int&, MAPA);

void tela_titulo(sf::RenderWindow&);
void titulo(sf::RenderWindow&, GameScreen&, sf::Clock &);

void tela_manual(sf::RenderWindow&);
void Manual(sf::RenderWindow&, int, GameScreen&, sf::Clock &);

void Menu(sf::RenderWindow&, GameScreen&, sf::Clock &);

void tela_creditos(sf::RenderWindow&);
void Creditos(sf::RenderWindow&, GameScreen&, sf::Clock &);

void legenda_gameplay(sf::RenderWindow&, GameScreen&, sf::Clock &);
#endif