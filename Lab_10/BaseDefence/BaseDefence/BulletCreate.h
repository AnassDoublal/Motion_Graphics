#pragma once
#include <SFML/Graphics.hpp>
#include "BulletUpdate.h"
#include <array>

class BulletCreate
{
public:
	/// <summary>
	/// creates the bullet at a given positon
	/// </summary>
	/// <param name="texture">bullet texture</param>
	/// <param name="x">x pos of bullet</param>
	/// <param name="y">y pos of bullet</param>
	/// <param name="rotation"> roation of bullet</param>
	void create(sf::Texture const& texture, double x, double y, double rotation);
	/// <summary>
	/// checks if the bullets are active or not
	/// and calls the update function for the active bullets
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="t_player"></param>
	void update(double dt, sf::Sprite t_player);
	/// <summary>
	/// renders the bullet on screen
	/// </summary>
	/// <param name="t_window">the display</param>
	void render(sf::RenderWindow& t_window);
	/// <summary>
	/// returns the bullet array
	/// </summary>
	/// <returns>bullet array</returns>
	std::array<BulletUpdate, 100>& getBullets();
private:
	// the maximum amount of bullet shown at once
	static const int BULLET_AMOUNT_SIZE = 100;

	// A container for the bullets.
	std::array<BulletUpdate, BULLET_AMOUNT_SIZE> m_bulletSprites;

	// The index of the next available bullet.
	int m_nextAvailable{ 0 };

	// A flag indicating whether there are any bullet available (initially they are).
	bool m_bulletContainerFull{ false };
};
