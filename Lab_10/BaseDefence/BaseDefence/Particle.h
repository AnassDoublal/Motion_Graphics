#pragma once
#include <SFML/Graphics.hpp>
class Particle
{
public:
	Particle() = default;
	/// <summary>
	/// Particle creation with start position and speed of the partical
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="vel"></param>
	Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color color);

	void render(sf::RenderWindow& t_window);
	void update();

private:

	int m_TTL; // time to live
	sf::Vector2f m_velocity; // speed of the partical
	sf::RectangleShape m_shape; // shape of the partical
	

};
