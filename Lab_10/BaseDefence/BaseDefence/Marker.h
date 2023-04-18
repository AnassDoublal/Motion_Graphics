#pragma once
#include <SFML/Graphics.hpp>
class Marker
{
public:
	// the marker gets created in the position it recieved from the enemy
	Marker(sf::Vector2f t_enemyPos);
	sf::CircleShape m_marker;
private:
	sf::Vector2f m_pos{-100,-100};
};