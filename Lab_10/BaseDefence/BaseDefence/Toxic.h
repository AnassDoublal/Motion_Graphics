#pragma once
#include "SFML/Graphics.hpp"

class Toxic
{
public:
	Toxic() = default;
	Toxic(sf::Texture& t_texture, sf::Texture& t_explosion, sf::Vector2f& t_pos);
	void update(double dt);
	void render(sf::RenderWindow& t_window);

	sf::Sprite m_explosion;
	sf::CircleShape m_animatedExplosion;
	sf::Sprite m_barrel;
	bool del = false;
	bool m_explosionHappened = false;
	double m_currentTime = 0; // the amount of time since barrel was hit
private:

	sf::Vector2f const getCenter(sf::IntRect t_rect);

	const double TTL = 1000; // time to live
	sf::IntRect m_rectBarrel{ 0,0,40,40 };
	sf::IntRect m_rectExplosion{ 0,0,100,100 };
};