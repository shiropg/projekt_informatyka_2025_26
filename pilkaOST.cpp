#include <SFML/Graphics.hpp>
#include <cmath>
#include "pilkaOST.h"

pilka::pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in) : x(x_in), y(y_in), vx(vx_in), vy(vy_in), radius(radius_in)
{
	ball.setRadius(radius);
	ball.setOrigin(radius, radius);
	ball.setPosition(x, y);
	ball.setFillColor(sf::Color::Red);
};

void pilka::move() {
	x += vx;
	y += vy;
	ball.setPosition(x, y);
};

void pilka::bounceX() {
	vx = -vx;
};

void pilka::bounceY() {
	vy = -vy;
};

void pilka::collideWalls(float width, float height) {
	if (x - radius <= 0 || x + radius >= width) {
		bounceX();
	};
	if (y - radius <= 0) {
		bounceY();
	};
};

bool pilka::collidePaddle(const paletka& p) {
	bool Xrange = x >= p.getX() - p.getSzerokosc() / 2 && x <= p.getX() + p.getSzerokosc() / 2;
	bool palleteTop = (y + radius) >= (p.getY() - p.getWysokosc() / 2) && (y - radius) < (p.getY() - p.getWysokosc() / 2);

	if (Xrange && palleteTop) {
		vy = -std::abs(vy);
		y = (p.getY() - p.getWysokosc() / 2) - radius;
		ball.setPosition(x, y);
		return true;
	}
	return false;
};

void pilka::collideBlock() {
	bounceY();
};

sf::FloatRect pilka::getBounds() const { return ball.getGlobalBounds(); };

void pilka::draw(sf::RenderTarget& target) {
	target.draw(ball);
};

float pilka::getX() const { return x; };
float pilka::getY() const { return y; };
float pilka::getVX() const { return vx; };
float pilka::getVY() const { return vy; };
float pilka::getRadius() const { return radius; };

void pilka::setBall(const sf::Vector2f& pos, const sf::Vector2f& vel) {
	x = pos.x;
	y = pos.y;
	vx = vel.x;
	vy = vel.y;
	ball.setPosition(x, y);
}