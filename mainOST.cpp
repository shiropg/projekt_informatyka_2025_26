/*
Temat projektu: Gra arkanoid
Zakres indywidualny: Gra polega na odbijaniu paletk¹ pi³ki i zbieraniu punktów. Jedno uderzenie to jeden punkt, zebranie kryszta³ka to dwa punkty.
Sterowanie: 
    Menu - strza³ki góra/dó³, enter
    Paletka - strza³ki prawo/lewo
    Zapis - litera P w trakcie rozgrywki
*/




#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "graOST.h"
#include "menuOST.h"
#include "aktualnyStanGryOST.h"

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow m_window(sf::VideoMode({ 640,600 }), "Arkanoid");
    m_window.setFramerateLimit(60);

    menu Menu(m_window.getSize().x, m_window.getSize().y);
    gra m_gra;

    GameState state = GameState::Menu;
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (state == GameState::Menu) {
                    if (event.key.code == sf::Keyboard::Up) {
                        Menu.przesunG();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        Menu.przesunD();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (Menu.getSelectedItem() == 0) {
                            m_gra.nowaGra();
                            state = GameState::Playing;
                        }
                        if (Menu.getSelectedItem() == 1) {
                            AktStanGry snapshot;
                            if (snapshot.loadFromFile("zapis.txt")) {
                                m_gra.resetPrzegranej();
                                snapshot.apply(m_gra.getPaletka(), m_gra.getPilka(), m_gra.getBloki(), m_gra);
                                state = GameState::Playing;
                            }
                            else {
                                std::cout << "Nie mozna wczytac zapisu" << std::endl;
                            }
                        }
                        else if (Menu.getSelectedItem() == 2) {
                            state = GameState::Scores;
                        }
                        else if (Menu.getSelectedItem() == 3) {
                            state = GameState::Exiting;
                        }
                    }
                };
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    sf::sleep(sf::seconds(1.f));
                    AktStanGry snapshot;
                    snapshot.capture(m_gra.getPaletka(), m_gra.getPilka(), m_gra.getBloki(), m_gra.getPunkty(), m_gra.getKrysztal());
                    if (snapshot.saveToFile("zapis.txt")) {
                        std::cout << "Gra zapisana!" << std::endl;
                    }
                }
            }
        }
        if (state == GameState::Playing) {
            m_gra.update();

            if (m_gra.isGameOver()) {
                state = GameState::Menu;
            }
        }

        m_window.clear(sf::Color(20, 20, 30));

        if (state == GameState::Menu) {
            Menu.draw(m_window);
        }
        else if (state == GameState::Playing) {
            m_gra.render(m_window);
        }
        if (state == GameState::Exiting) {
            m_window.close();
        }

        m_window.display();
    };
    return 0;
}
