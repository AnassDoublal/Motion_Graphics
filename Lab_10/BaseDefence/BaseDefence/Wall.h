#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "Grid.h"

int const WALL_AMOUNT = 100;

class Wall
{
public:
	/// <summary>
	/// Wall default constructor
	/// </summary>
	Wall();
	/// <summary>
	/// Construct wall
	/// </summary>
	/// <param name="t_texture">Wall texture</param>
	/// <param name="i">i index</param>
	/// <param name="j">j index</param>
	Wall(sf::Texture&, int, int);
	/// <summary>
	/// Initialize Wall
	/// </summary>
	/// <param name="t_texture">Wall texture</param>
	/// <param name="i">i index</param>
	/// <param name="j">j index</param>
	void init(sf::Texture&, int, int);
	/// <summary>
	/// Update wall
	/// </summary>
	void update();
	/// <summary>
	/// Render wall
	/// </summary>
	/// <param name="t_window">Game window</param>
	void render(sf::RenderWindow&);

	sf::Sprite m_wall;
	sf::Vector2f m_wallSize;

	bool m_wallWasHit = false;
	int m_wallCell;

private:
	sf::IntRect m_rect = { 0, 0, 5, 5 };
	sf::Vector2f const getWallCenter();
};