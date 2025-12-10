#pragma once
#include <SFML/Graphics.hpp>

class krysztal {
private:
	sf::ConvexShape crystal;
	float m_windowWidth;
	float m_windowHeight;
public:
	krysztal();
	void losujPozycje(float windowWidth, float windowHeight);

	sf::FloatRect getGlobalBounds() const;
	void draw(sf::RenderTarget& target);

	sf::Vector2f getPosition() const;
	void setPosition(float x, float y);
};