#include "Toxic.h"

Toxic::Toxic(sf::Texture& t_texture, sf::Texture& t_explosion, sf::Vector2f& t_pos)
{
	m_barrel.setTexture(t_texture);
	m_barrel.setPosition(t_pos);
	m_barrel.setOrigin(getCenter(m_rectBarrel));

	m_explosion.setTexture(t_explosion);
	m_explosion.setPosition(t_pos);
	m_explosion.setOrigin(getCenter(m_rectExplosion));

	m_animatedExplosion.setRadius(50);
	m_animatedExplosion.setFillColor(sf::Color::White);
	m_animatedExplosion.setPosition(t_pos);
	m_animatedExplosion.setOrigin(50.0f, 50.0f);
}

void Toxic::update(double dt)
{
	// if explosion happened start the explosions time too live
	if (m_explosionHappened == true)
	{
		m_animatedExplosion.setRadius(m_animatedExplosion.getRadius() + 2);
		m_animatedExplosion.setOrigin(m_animatedExplosion.getOrigin().x + 2.0f, m_animatedExplosion.getOrigin().x + 2.0f);
		if(m_animatedExplosion.getFillColor().g >= 5 && m_animatedExplosion.getFillColor().b >= 7)
			m_animatedExplosion.setFillColor(sf::Color(255, m_animatedExplosion.getFillColor().g - 5, m_animatedExplosion.getFillColor().b - 7, 255));

		m_currentTime += dt;
		if (m_currentTime > TTL)
		{
			del = true;
			m_explosionHappened = false;
			m_currentTime = 0;
		}
	}
	
}

void Toxic::render(sf::RenderWindow& t_window)
{
	// if explosion didnt happen, draw barrel
	if (m_explosionHappened == false)
	{
	t_window.draw(m_barrel);
	}
	// if it happened draw explosion
	else
	{
		t_window.draw(m_animatedExplosion);
	}
}

sf::Vector2f const Toxic::getCenter(sf::IntRect t_rect)
{
	sf::Vector2f origin;

	origin.x = t_rect.width / 2.0f;
	origin.y = t_rect.height / 2.0f;

	return origin;
}
