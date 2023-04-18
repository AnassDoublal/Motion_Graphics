#include "Particle.h"

void Particle::render(sf::RenderWindow& t_window)
{
	if (m_TTL > 0)
	{
		t_window.draw(m_shape);
	}
	
}

void Particle::update()
{
	if (m_TTL > 0)
	{
		m_shape.move(m_velocity);

		m_TTL--;
	}

}

Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Color color)
{
	m_shape.setSize(sf::Vector2f(6, 6));
	m_shape.setPosition(pos);
	m_shape.setFillColor(color);
	
	m_velocity = vel;
	m_TTL = rand() % 150;
}
