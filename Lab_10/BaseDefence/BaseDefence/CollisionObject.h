#pragma once
#include "SFML/Graphics.hpp"
class CollisionObject
{
public:
	/// <summary>
	/// creates the collision object based on the dimensions of the Sprite object
	/// </summary>
	/// <param name="Object"></param>
	CollisionObject(const sf::Sprite& Object);
	CollisionObject(const sf::CircleShape& Object);

	sf::Vector2f Points[4];

	// projects the points onto an axis
	void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max);
private:

};