#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include <Thor/Vectors.hpp>
#include <Thor/Math.hpp>

class BulletUpdate
{
	friend class BulletCreate;

public:

	/// <summary>
	/// initiates the starting position of the bullet
	/// </summary>
	/// <param name="texture">bullets texture</param>
	/// <param name="x">the x pos of the bullet</param>
	/// <param name="y">the y pos of the bullet</param>
	/// <param name="rotation"> the ortation of the bullet</param>
	void init(sf::Texture const& texture, double x, double y, double rotation);
	/// <summary>
	/// updates the position of the bullet
	/// </summary>
	/// <param name="dt">delta time</param>
	/// <param name="t_player">the player sprite</param>
	/// <returns>if the bullet is in use or not</returns>
	bool update(double dt, sf::Sprite t_player);
	/// <summary>
	/// checks if the bullet is currently being used
	/// </summary>
	/// <returns></returns>
	bool inUse() const;
	// A sprite for the bullet.
	sf::Sprite m_bulletSprite;
	double m_speed{ MAX_SPEED };
private:
	/// <summary>
	/// checks if the bullet is within the bounds of the screen
	/// </summary>
	/// <param name="position">the bullets positon</param>
	/// <returns></returns>
	bool isOnScreen(sf::Vector2f position) const;
	// Max speed 
	const double MAX_SPEED = 1000.0;

	// initial Movement speed.
	
	/// <summary>
	/// rectangle box of the bullet
	/// </summary>
	sf::IntRect m_bulletRect{ 0, 0, 10, 10 };
};