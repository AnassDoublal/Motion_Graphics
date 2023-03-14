#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

sf::Texture extern coinTexture;

class Coin {
public:
	void loadTexture();
	void init();
	void update();
	sf::Sprite& getCoin();
private:
	sf::Sprite coin;
};