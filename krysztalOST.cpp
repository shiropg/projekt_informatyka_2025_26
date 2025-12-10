#include "krysztalOST.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

krysztal::krysztal() {
	crystal.setPointCount(8);
	crystal.setPoint(0, sf::Vector2f(0.f, -30.f));
	crystal.setPoint(1, sf::Vector2f(10.f, -10.f));
	crystal.setPoint(2, sf::Vector2f(25.f, 5.f));
	crystal.setPoint(3, sf::Vector2f(10.f, 15.f));
	crystal.setPoint(4, sf::Vector2f(-5.f, 40.f));
	crystal.setPoint(5, sf::Vector2f(-15.f, 15.f));
	crystal.setPoint(6, sf::Vector2f(-35.f, 0.f));
	crystal.setPoint(7, sf::Vector2f(-10.f, 10.f));
	crystal.setFillColor(sf::Color(255, 105, 180));
	crystal.setPosition(-100.f, -100.f);
}

void krysztal::losujPozycje(float windowWidth, float windowHeight) {
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	float x = 60.f + static_cast<float>(rand() % static_cast<int>(windowWidth - 120.f));
	float y = 60.f + static_cast<float>(rand() % static_cast<int>(windowHeight - 250.f));
	crystal.setPosition(x, y);
};

sf::FloatRect krysztal::getGlobalBounds() const {
	return crystal.getGlobalBounds();
};

void krysztal::draw(sf::RenderTarget& target) {
	target.draw(crystal);
};

sf::Vector2f krysztal::getPosition() const {
	return crystal.getPosition();
};

void krysztal::setPosition(float x, float y) {
	crystal.setPosition(x, y);
};