#include "Coin.h"

sf::Texture& Coin::loadTexture()
{
	sf::Texture coinTexture;

	if (!coinTexture.loadFromFile("coin.png"))
	{
		// Error
	}

	return coinTexture;
}

void Coin::init(sf::Texture& t_texture)
{
	coin.setScale(.100604, .100604);
	coin.setTexture(t_texture);
}

sf::Sprite& Coin::getCoin()
{
	return coin;
}
