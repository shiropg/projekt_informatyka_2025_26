#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 4

class menu
{
private:
	sf::Font font;
	sf::Text Menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;
public:
	menu(float width, float height);
	~menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
};