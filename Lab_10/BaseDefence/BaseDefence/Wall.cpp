#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(sf::Texture& t_texture, int i, int j)
{
	init(t_texture, i, j);
}

void Wall::init(sf::Texture& t_texture, int i, int j)
{
	m_wallSize.x = m_rect.width;
	m_wallSize.y = m_rect.height;
	m_wall.setTexture(t_texture);
	m_wall.setOrigin(getWallCenter());
	m_wall.setTextureRect(m_rect);
	m_wall.setPosition(475 + i * 5, 200 + j * 5);
	m_wallCell = ((200 + j * 5) * NUM_COLS + (475 + i * 5));
	//m_wallCell = (475 + i * 5) + (200 + j * 5);
}

void Wall::update()
{
}

void Wall::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_wall);
}

sf::Vector2f const Wall::getWallCenter()
{
	sf::Vector2f origin;

	origin.x = m_rect.width / 2.0f;
	origin.y = m_rect.height / 2.0f;

	return origin;
}
