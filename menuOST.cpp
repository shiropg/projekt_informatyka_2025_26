#include <SFML/Graphics.hpp>
#include <iostream>
#include "menuOST.h"

menu::menu(float width, float height)
{
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		return;
	}

	Menu[0].setFont(font);
	Menu[0].setFillColor(sf::Color::Cyan);
	Menu[0].setString("Nowa gra");
	Menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 1));

	Menu[1].setFont(font);
	Menu[1].setFillColor(sf::Color::White);
	Menu[1].setString("Wczytaj gre");
	Menu[1].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	
	Menu[2].setFont(font);
	Menu[2].setFillColor(sf::Color::White);
	Menu[2].setString("Ostatnie wyniki");
	Menu[2].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 3));

	Menu[3].setFont(font);
	Menu[3].setFillColor(sf::Color::White);
	Menu[3].setString("Wyjscie");
	Menu[3].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 4));
}

void menu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
		window.draw(Menu[i]);
	}
}

void menu::przesunG() {
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) {
		Menu[selectedItem].setFillColor(sf::Color::White);
		Menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
	}
	if (selectedItem < 0) {
		selectedItem = MAX_LICZBA_POZIOMOW - 1;
	}
	Menu[selectedItem].setFillColor(sf::Color::Cyan);
	Menu[selectedItem].setStyle(sf::Text::Bold);
}

void menu::przesunD() {
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) {
		Menu[selectedItem].setFillColor(sf::Color::White);
		Menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
	}
	if (selectedItem >= MAX_LICZBA_POZIOMOW) {
		selectedItem = 0;
	}
	Menu[selectedItem].setFillColor(sf::Color::Cyan);
	Menu[selectedItem].setStyle(sf::Text::Bold);
}

void myDelay(int opoznienie) {
	sf::Clock zegar;
	sf::Time czas;
	while (1) {
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie) {
			zegar.restart();
			break;
		}
	}
}