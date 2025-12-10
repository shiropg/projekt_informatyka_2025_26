#include <SFML/Graphics.hpp>
#include "paletkaOST.h"
#include "graOST.h"

paletka::paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in) : x(x_in), y(y_in), szerokosc(szerokosc_in), wysokosc(wysokosc_in), predkosc(predkosc_in)
{
	pallet.setSize({ szerokosc, wysokosc });
	pallet.setOrigin(szerokosc / 2, wysokosc / 2);
	pallet.setFillColor(sf::Color::Blue);
	pallet.setPosition(x, y);
};

void paletka::moveLeft() {
	x -= predkosc;
	pallet.setPosition(x, y);
};

void paletka::moveRight() {
	x += predkosc;
	pallet.setPosition(x, y);
};

void paletka::clampToBounds(float width) {
	if (x - szerokosc / 2 < 0) {
		x = szerokosc / 2;
	};
	if (x + szerokosc / 2 > width) {
		x = width - szerokosc / 2;
	};
	pallet.setPosition(x, y);
};

void paletka::draw(sf::RenderTarget& target) {
	target.draw(pallet);
};

float paletka::getX() const { return x; };
float paletka::getY() const { return y; };
float paletka::getSzerokosc() const { return szerokosc; };
float paletka::getWysokosc() const { return wysokosc; };

void paletka::setPosition(const sf::Vector2f& pos) {
	x = pos.x;
	y = pos.y;
	pallet.setPosition(pos);
}