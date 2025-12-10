#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "paletkaOST.h"

class pilka {
private:
	sf::Vector2f position;
	float x;
	float y;
	float vx;
	float vy;
	float radius;
	sf::CircleShape ball;
public:
	pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in);

	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	bool collidePaddle(const paletka& p);
	void collideBlock();

	sf::FloatRect getBounds() const;
	void draw(sf::RenderTarget& target);

	float getX() const;
	float getY() const;
	float getVX() const;
	float getVY() const;
	float getRadius() const;

	void setBall(const sf::Vector2f& pos, const sf::Vector2f& vel);
};

