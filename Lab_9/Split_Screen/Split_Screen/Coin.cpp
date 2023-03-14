#include "Coin.h"

void Coin::loadTexture()
{
	if (!coinTexture.loadFromFile("coin.png"))
	{
		// Error
	}

	std::cout << "LOADED TEXTURE\n";
}

void Coin::init()
{
	coin.setScale(.100604, .100604);
	coin.setTexture(coinTexture);
}

sf::Sprite& Coin::getCoin()
{
	return coin;
}
