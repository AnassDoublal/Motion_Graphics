#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
public:

	Platform() = default;

	Platform(sf::Texture& , sf::Vector2f);
	
	void init(sf::Texture&, sf::Vector2f);
	void render(sf::RenderWindow&);
	void setOnPlatform(bool&);
	bool isOnPlatform();
	sf::Sprite m_platform;
	sf::Vector2f m_platformSize;
private:
	bool m_onPlatform = false;
	sf::IntRect m_rect = { 0, 0, 40, 40 };
	sf::Vector2f const getPlatformCenter();
private:
};