#pragma once
#include "SFML/Graphics.hpp"
#include "CollisionObject.h"

class Collisions
{
public:
	Collisions() = default;
	// checks the collision of two sprite objects
	bool collision(sf::Sprite& t_obj1, sf::Sprite& t_obj2);
	bool collision(sf::CircleShape& t_obj1, sf::Sprite& t_obj2);
};