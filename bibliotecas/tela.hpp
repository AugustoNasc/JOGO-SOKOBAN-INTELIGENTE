#ifndef TELA_HPP
#define TELA_HPP

typedef enum GameScreen { TITLE, MANUAL1, MANUAL2, ESCOLHER_NIVEL, CREDITO, GAMEPLAY, PARABENS } GameScreen;

namespace tl{
    void tela_titulo(sf::RenderWindow&);
    void titulo(sf::RenderWindow&, GameScreen&, sf::Clock &);

    void tela_manual(sf::RenderWindow&);
    void Manual(sf::RenderWindow&, int, GameScreen&, sf::Clock &);

    void tela_creditos(sf::RenderWindow&);
    void Creditos(sf::RenderWindow&, GameScreen&, sf::Clock &);

    void legenda_gameplay(sf::RenderWindow&, GameScreen&, sf::Clock &);
}
#endif