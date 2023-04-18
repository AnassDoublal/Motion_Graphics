#pragma once
#include "SFML/Graphics.hpp"

int const HIVE_AMOUNT = 4;

class Hive
{
public:
	Hive(sf::Texture& const, int const);
	/// <summary>
	/// Initialize hive
	/// </summary>
	/// <param name="t_texture">Apply single texture to all hives</param>
	void init(sf::Texture&, int const);
	/// <summary>
	/// Update hive
	/// </summary>
	void update();
	/// <summary>
	/// Render hive
	/// </summary>
	void render(sf::RenderWindow& t_window);

	sf::Sprite m_hive;
	sf::Vector2f m_hiveSize;
private:
	sf::Vector2f m_pos[HIVE_AMOUNT] = 
	{ {50.0f, 50.0f},
	  {1390.0f, 50.0f},
	  {1390.0f, 800.0f},
	  {50.0f, 800.0f}
	}; 
	sf::IntRect m_rect = {0, 0, 60, 60};
	sf::Vector2f const getHiveCenter();
};