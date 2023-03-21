#pragma once
#include "random"
#include "SFML/Graphics.hpp"
#include "Coin.h"
#include "iostream"

class Level {
public:
	void init();
	void update();
	void render(sf::RenderWindow&);
	sf::RectangleShape level[50][50];
	Coin coins[2];
private:
	int const rows = 50;
	int const cols = 50;
	int levelData[50][50];
	float const tileWidth = 50.0f;
	float const tileHeight = 50.0f;
};