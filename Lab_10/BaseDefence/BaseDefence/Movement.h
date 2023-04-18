#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
class Movement
{
public:
	Movement() = default;

	// change the position of the player by an offset of recoil, depending on the direction the player faces
	sf::Vector2f recoilControl(sf::Vector2f t_pos, int t_faceDir);
private:

	float recoil = 0.5f;

};
