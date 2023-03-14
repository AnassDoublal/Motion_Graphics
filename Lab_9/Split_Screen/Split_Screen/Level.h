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
private:
	int const rows = 50;
	int const cols = 50;
	int levelData[50][50];
	sf::RectangleShape level[50][50];
	float const tileWidth = 50.0f;
	float const tileHeight = 50.0f;
	Coin coins[20];
};