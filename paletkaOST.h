#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>

class paletka {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float predkosc;
	sf::RectangleShape pallet;
	sf::Vector2f m_position;
public:
	paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in);

	void moveLeft();
	void moveRight();
	void clampToBounds(float width);

	void draw(sf::RenderTarget& target);

	float getX() const;
	float getY() const;
	float getSzerokosc() const;
	float getWysokosc() const;

	void setPosition(const sf::Vector2f& pos);
};

