#include "Pulse.h"

Pulse::Pulse()
{
}

void Pulse::update(double dt)
{
	m_currentTime += dt;
	// checks if radius is within the bounds of the screen
	shouldPulseGrow();
	if (m_currentTime >= 1000)
	{
		showMarkers = true;
		// changes the radius by a positive or a negative depending on if we cant it to expand or contract at the moment
		if (m_increasePulse)
		{
			m_radius += m_radiusTransformation;
		}
		else
		{
			m_radius -= m_radiusTransformation;
		}
		m_pulse.setRadius(m_radius); // updates the radius
		m_pulse.setOrigin(getOriginPoint());
	}
	else
	{
		showMarkers = false;
		m_markers.clear();
	}
}

void Pulse::init(const sf::Vector2f& t_startingPos)
{
	m_pulse.setPosition(t_startingPos);
	m_pulse.setRadius(m_radius);
	m_pulse.setOrigin(getOriginPoint());
	m_pulse.setFillColor(sf::Color(135, 206, 250, 50));
	m_pulse.setPointCount(100);
}
void Pulse::shouldPulseGrow()
{
	sf::Vector2f pulseEdge;
	pulseEdge.x = m_pulse.getPosition().x + m_radius;
	pulseEdge.y = m_pulse.getPosition().y + m_radius;

	if (pulseEdge.x >= 1440 && pulseEdge.y >= 900)
	{
		m_increasePulse = false;
	}
	if (pulseEdge.y <= m_pulse.getPosition().y)
	{
		m_radius += 10;
		m_increasePulse = true;
		m_currentTime = 0;
	}
}
const sf::Vector2f Pulse::getOriginPoint()
{
	sf::Vector2f newOrigin;
	newOrigin.x = m_radius;
	newOrigin.y = m_radius;
	return sf::Vector2f(newOrigin);
}
void Pulse::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_pulse);
	if (showMarkers)
	{
		for (size_t i = 0; i < m_markers.size(); i++)
		{
			t_window.draw(m_markers[i].m_marker);
		}
	}
	
}