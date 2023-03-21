#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "Coin.h"

enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

class Collision
{
public:
	Direction playerToWall(sf::Sprite&, sf::RectangleShape[][50]);
	bool playerToCoin(sf::Sprite&, Coin&);
};