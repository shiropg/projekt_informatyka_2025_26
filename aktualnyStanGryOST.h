#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "pilkaOST.h"
#include "paletkaOST.h"
#include "kamienOST.h"
#include "krysztalOST.h"

struct BlockData {
    float x, y;
    int hp;
};

class gra;

class AktStanGry {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
    int zapisanePunkty;
    sf::Vector2f crystalPosition;
public:
    void capture(const paletka& paddle,
        const pilka& ball,
        const std::vector<kamien>& stones,
        int punkty,
        const krysztal& crystal);

    bool saveToFile(const std::string& filename) /*const*/;
    bool loadFromFile(const std::string& filename);

    void apply(paletka& paddle, pilka& ball, std::vector<kamien>& stones, gra& gameRef);
};