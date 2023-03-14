#pragma once
#include "SFML/Graphics.hpp"

class Coin {
public:
	sf::Texture& loadTexture();
	void init(sf::Texture&);
	void update();
	sf::Sprite& getCoin();
private:
	sf::Sprite coin;
};