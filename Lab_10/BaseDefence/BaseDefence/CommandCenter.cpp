#include "CommandCenter.h"

CommandCenter::CommandCenter()
{
}

CommandCenter::CommandCenter(sf::Texture& t_texture)
{
	init(t_texture);
}

void CommandCenter::init(sf::Texture& t_texture)
{
	m_commandCenterSize.x = m_rect.width;
	m_commandCenterSize.y = m_rect.height;
	m_commandCenter.setTexture(t_texture);
	m_commandCenter.setOrigin(getCommandCenterCenter());
	m_commandCenter.setTextureRect(m_rect);
	m_commandCenter.setPosition(725.0f, 450.0f);
	pulseObj.init(m_commandCenter.getPosition());
}

void CommandCenter::update(double dt)
{
	/*for (size_t i = 0; i < ENEMY_AMOUNT; i++)
	{

	}*/
	pulseObj.update(dt);
	
}

void CommandCenter::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_commandCenter);
	pulseObj.render(t_window);
	
}

sf::Vector2f const CommandCenter::getCommandCenterCenter()
{
	sf::Vector2f origin;

	origin.x = m_rect.width / 2.0f;
	origin.y = m_rect.height / 2.0f;

	return origin;
}
