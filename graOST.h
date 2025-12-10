#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "pilkaOST.h"
#include "paletkaOST.h"
#include "kamienOST.h"
#include "krysztalOST.h"

class gra {
private:
	paletka m_paletka;
	pilka m_pilka;
	std::vector<kamien> m_bloki;
	krysztal m_krysztal;

	sf::Font m_czcionka;
	sf::Text m_drukWyniku;
	void aktualizujTekst();

	int liczKlatki = 0;
	static constexpr float WIDTH = 640.f;
	static constexpr float HEIGHT = 480.f;
	bool game_over = false;
	int m_punkty;
public:
	gra();

	void nowaGra();
	void update();
	void render(sf::RenderTarget& target);
	bool isGameOver() const;

	void resetPrzegranej();

	paletka& getPaletka();
	pilka& getPilka();
	std::vector<kamien>& getBloki();

	int getPunkty() const { return m_punkty; };
	void setPunkty(int pkt) {
		m_punkty = pkt;
		aktualizujTekst();
	}
	krysztal& getKrysztal() { return m_krysztal; };
};