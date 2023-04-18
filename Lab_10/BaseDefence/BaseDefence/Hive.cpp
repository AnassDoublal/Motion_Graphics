#include "Hive.h"

// Construct hive
Hive::Hive(sf::Texture& const t_texture, int const t_index)
{
	init(t_texture, t_index);
}

// Initialize hive
void Hive::init(sf::Texture& const t_texture, int const t_index)
{
	m_hiveSize.x = m_rect.width;
	m_hiveSize.y = m_rect.height;
	m_hive.setTexture(t_texture);
	m_hive.setPosition(m_pos[t_index]);
	m_hive.setOrigin(getHiveCenter());
	m_hive.setTextureRect(m_rect);
}

// Update hive
void Hive::update()
{
}

// Render hive
void Hive::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_hive);
}

// Get center of hive 
sf::Vector2f const Hive::getHiveCenter()
{
	sf::Vector2f origin;

	origin.x = m_rect.width / 2.0f;
	origin.y = m_rect.height / 2.0f;

	return origin;
}
