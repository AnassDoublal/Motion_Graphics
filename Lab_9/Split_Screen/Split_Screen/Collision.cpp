#include "Collision.h"

Direction& Collision::playerToWall(sf::Sprite& player, sf::RectangleShape level[][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (player.getGlobalBounds().intersects(level[i][j].getGlobalBounds()))
			{
				if (level[i][j].getFillColor() == sf::Color::Green)
				{
					if (player.getPosition().x < level[i][j].getPosition().x)
						direction = Direction::LEFT;
					else if (player.getPosition().x > level[i][j].getPosition().x)
						direction = Direction::RIGHT;
					else if (player.getPosition().y < level[i][j].getPosition().y)
						direction = Direction::UP;
					else if (player.getPosition().y > level[i][j].getPosition().y)
						direction = Direction::DOWN;
				}
			}
		}
	}
	return direction;
}
