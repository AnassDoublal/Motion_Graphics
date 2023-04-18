#include "Marker.h"

Marker::Marker(sf::Vector2f t_enemyPos) : m_pos(t_enemyPos)
{
	m_marker.setPosition(m_pos);
	m_marker.setFillColor(sf::Color::Green);
	m_marker.setRadius(3);
}
