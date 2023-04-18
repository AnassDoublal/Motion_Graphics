#include "Platform.h"

Platform::Platform(sf::Texture& t_texture, sf::Vector2f t_pos)
{
	init(t_texture, t_pos);
}

void Platform::init(sf::Texture& t_texture, sf::Vector2f t_pos)
{
	m_platformSize.x = m_rect.width;
	m_platformSize.y = m_rect.height;
	m_platform.setTexture(t_texture);
	m_platform.setOrigin(getPlatformCenter());
	m_platform.setTextureRect(m_rect);
	m_platform.setPosition(t_pos);
}

void Platform::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_platform);
}

void Platform::setOnPlatform(bool& t_true)
{
	m_onPlatform = t_true;
}

bool Platform::isOnPlatform()
{
	return m_onPlatform;
}

sf::Vector2f const Platform::getPlatformCenter()
{
	sf::Vector2f origin;

	origin.x = m_rect.width / 2.0f;
	origin.y = m_rect.height / 2.0f;

	return origin;
}
