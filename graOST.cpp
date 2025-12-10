#pragma once

#include <SFML/Graphics.hpp> 
#include "graOST.h"
#include "paletkaOST.h"
#include "pilkaOST.h"
#include "kamienOST.h"
#include "aktualnyStanGryOST.h"
#include "krysztalOST.h"

gra::gra() : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f), m_pilka(320.f, 260.f, 4.f, 3.f, 8.f)
{
	if (!(m_czcionka.loadFromFile("C:/Windows/Fonts/arial.ttf"))) {
		std::cout << "BLAD! Nie znaleziono pliku arial." << std::endl;
	};

	m_drukWyniku.setFont(m_czcionka);
	m_drukWyniku.setCharacterSize(24);
	m_drukWyniku.setFillColor(sf::Color::White);
	nowaGra();
};

void gra::nowaGra() {
	m_punkty = 0;
	game_over = false;
	liczKlatki = 0;

	m_paletka = paletka(320.f, 440.f, 100.f, 20.f, 8.f);
	m_pilka = pilka(320.f, 260.f, 4.f, 3.f, 8.f);

	m_bloki.clear();
	const int ILOSC_KOLUMN = 6;
	const int ILOSC_WIERSZY = 7;
	const float ROZMIAR_BLOKU_Y = 25.f;
	const float ROZMIAR_BLOKU_X = (640 - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

	for (int i = 0; i < ILOSC_WIERSZY; i++) {
		for (int j = 0; j < ILOSC_KOLUMN; j++) {
			float posX = j * ROZMIAR_BLOKU_X + j * 2.f;
			float posY = i * ROZMIAR_BLOKU_Y + i * 2.f + 50.f;

			int L = (i < 1) ? 3 : (i < 3) ? 2 : 1;

			m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
		}
	}
	m_krysztal.losujPozycje(WIDTH, HEIGHT);
	aktualizujTekst();
}

void gra::aktualizujTekst() {
	m_drukWyniku.setString("Wynik: " + std::to_string(m_punkty));

	sf::FloatRect bounds = m_drukWyniku.getLocalBounds();
	m_drukWyniku.setOrigin(bounds.width, bounds.height);
	m_drukWyniku.setPosition(WIDTH - 10.f, HEIGHT - 10.f);
}

void gra::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_paletka.moveLeft();
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_paletka.moveRight();
	};
	m_paletka.clampToBounds(WIDTH);
	
	m_pilka.move();
	m_pilka.collideWalls(WIDTH, HEIGHT);

	if (m_pilka.collidePaddle(m_paletka)) {
		std::cout << "HIT PADDLE\n";
	};

	if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
		std::cout << "MISS! KONIEC GRY\n";
		game_over = true;
	};

	liczKlatki++;
	if (liczKlatki % 20 == 0) {
		std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY() << " vx=" << m_pilka.getVX() << " vy=" << m_pilka.getVY() << std::endl;
	};

	if (m_pilka.getBounds().intersects(m_krysztal.getGlobalBounds())) {
		m_punkty += 2;
		m_krysztal.losujPozycje(WIDTH, HEIGHT);
		aktualizujTekst();
	};
}

void gra::render(sf::RenderTarget& target) {
	m_pilka.draw(target);
	m_paletka.draw(target);
	for (auto& b : m_bloki) {
		if (b.isDestroyed() == false) {
			if (m_pilka.getBounds().intersects(b.getGlobalBounds())) {
				m_pilka.collideBlock();
				b.trafienie();
				m_punkty += 1;
				aktualizujTekst();
				std::cout << "Wynik: " << m_punkty << std::endl;
			}
		}
		b.draw(target);
	}
	m_krysztal.draw(target);
	target.draw(m_drukWyniku);
}

bool gra::isGameOver() const { return game_over; };

void gra::resetPrzegranej() {
	game_over = false;
};

paletka& gra::getPaletka() { return m_paletka; };
pilka& gra::getPilka() { return m_pilka; };
std::vector<kamien>& gra::getBloki() { return m_bloki; };
