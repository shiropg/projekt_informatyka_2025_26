#include "aktualnyStanGryOST.h"
#include <fstream>
#include <iostream>
#include <string>
#include "graOST.h"

bool AktStanGry::saveToFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	};

	file << "PALETKA " << paddlePosition.x << " " << paddlePosition.y << "\n";
	file << "PILKA " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
	file << "LICZBA_BLOKOW " << blocks.size() << " " << "\n";
	for(const auto & block:blocks) {
		file << block.x << " " << block.y << " " << block.hp << "\n";
	}
	file << "WYNIK " << zapisanePunkty << "\n";
	file << "KRYSZTAL " << crystalPosition.x << " " << crystalPosition.y << "\n";

	file.close();
	return true;
}

void AktStanGry::capture(const paletka& paddle,
	const pilka& ball,
	const std::vector<kamien>& stones,
	int punkty,
	const krysztal& crystal)
{
	paddlePosition = sf::Vector2f(paddle.getX(), paddle.getY());

	ballPosition = sf::Vector2f(ball.getX(), ball.getY());
	ballVelocity = sf::Vector2f(ball.getVX(), ball.getVY());

	blocks.clear();
	blocks.reserve(stones.size());
	for (const auto& s : stones) {
		if (!s.isDestroyed()) {
			BlockData data;
			data.x = s.getPosition().x;
			data.y = s.getPosition().y;
			data.hp = s.getHP();
			blocks.push_back(data);
		}
	};

	zapisanePunkty = punkty;
	crystalPosition = crystal.getPosition();
}

bool AktStanGry::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	};

	std::string label;

	if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;
	if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;
	int blocksCount;
	if (!(file >> label >> blocksCount)) return false;

	for (int i = 0; i < blocksCount; i++) {
		float x, y;
		int hp;
		if (!(file >> x >> y >> hp)) return false;
		blocks.push_back({ x, y, hp });
	}
	if (!(file >> label >> zapisanePunkty)) return false;
	if (!(file >> label >> crystalPosition.x >> crystalPosition.y)) return false;

	file.close();
	return true;
}

void AktStanGry::apply(paletka& paddle, pilka& ball, std::vector<kamien>& stones, gra& gameRef) {
	paddle.setPosition(paddlePosition);
	ball.setBall(ballPosition, ballVelocity);
	stones.clear();
	for (const auto& data : blocks) {
		int ILOSC_KOLUMN = 6;
		const float ROZMIAR_BLOKU_Y = 25.f;
		const float ROZMIAR_BLOKU_X = (640 - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
		sf::Vector2f size(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y);
		stones.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp);
	}
	gameRef.setPunkty(zapisanePunkty);
	gameRef.getKrysztal().setPosition(crystalPosition.x, crystalPosition.y);
}