#include "Light.h"

candle::LightingArea m_fog(candle::LightingArea::FOG,
						   sf::Vector2f(0.f, 0.f),
						   sf::Vector2f(1440.0f, 900.0f));

void Light::init()
{
	m_light.setRange(350);
	m_light.setColor(sf::Color::White);

	m_circle.setOrigin(350, 350);
	m_circle.setRadius(350);
	m_circle.setFillColor(sf::Color::Color(255, 255, 255, 127));

	m_fog.setAreaColor(sf::Color::Black);

}

void Light::update(Player& t_player)
{
	m_circle.setPosition(t_player.m_playerSprite.getPosition());
	m_light.setPosition(t_player.m_playerSprite.getPosition());
}

void Light::render(sf::RenderWindow& t_window)
{
	m_fog.clear();
	m_fog.draw(m_light);
	m_fog.display();

	t_window.draw(m_fog);
}
