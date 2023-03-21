#include "Collision.h"

Direction Collision::playerToWall(sf::Sprite& player, sf::RectangleShape level[][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (player.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
			{
				if (level[i][j].getFillColor() == sf::Color::Color(42, 157, 143))
				{
					if (player.getPosition().x - 5.0f < level[i][j].getPosition().x)
						return Direction::LEFT;
					else if (player.getPosition().x + 5.0f > level[i][j].getPosition().x + level[i][j].getGlobalBounds().width + 25.0f)
						return Direction::RIGHT;
					else if (player.getPosition().y - 5.0f < level[i][j].getPosition().y)
						return Direction::UP;
					else if (player.getPosition().y + 15.0f > level[i][j].getPosition().y + level[i][j].getGlobalBounds().height)
						return Direction::DOWN;
				}
			}
		}
	}
	return Direction::NONE;
}

bool Collision::playerToCoin(sf::Sprite& player, Coin& coin)
{
	if (player.getGlobalBounds().intersects(coin.getCoin().getGlobalBounds()))
	{
		return true;
	}
	return false;
}
