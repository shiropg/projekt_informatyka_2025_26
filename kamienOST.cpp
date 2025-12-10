#include <SFML/Graphics.hpp> 
#include "kamienOST.h"

const std::array<sf::Color, 4> kamien::m_colorLUT = {
        sf::Color::Transparent, 
        sf::Color::Red,        
        sf::Color::Yellow,      
        sf::Color::Blue         
};

kamien::kamien(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) : m_punktyZycia(L), m_jestZniszczony(false) {
	this->setPosition(startPos);
	this->setSize(rozmiar);
	setOutlineThickness(2.f);
	aktualizujKolor();
};

void kamien::trafienie() {
	if (m_jestZniszczony == true) {
		return;
	};
	m_punktyZycia -= 1;
	aktualizujKolor();
	if (m_punktyZycia <= 0) {
		m_jestZniszczony = true;
	};
};

void kamien::aktualizujKolor() {
	if (m_punktyZycia >= 0 && static_cast<std::size_t>(m_punktyZycia) < m_colorLUT.size()) {
		this->setFillColor(m_colorLUT[m_punktyZycia]);
	}
	else {};
};

bool kamien::isDestroyed() const { return m_jestZniszczony; };

void kamien::draw(sf::RenderTarget& target) const {
	if (m_jestZniszczony == false) {
		target.draw(*this);
	};
};

int kamien::getHP() const { return m_punktyZycia; };
sf::Vector2f kamien::getPos() const { return getPosition(); };