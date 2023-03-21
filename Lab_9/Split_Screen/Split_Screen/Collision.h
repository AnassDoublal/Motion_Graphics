#pragma once
#include "SFML/Graphics.hpp"

enum class Direction { LEFT, RIGHT, UP, DOWN };

class Collision
{
public:
	Direction direction;
	Direction& playerToWall(sf::Sprite&, sf::RectangleShape[][50]);
private:
};