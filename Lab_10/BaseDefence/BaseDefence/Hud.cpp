#include "Hud.h"

Hud::Hud(sf::Font& t_font)
{
	m_score.setFont(t_font);
	m_score.setString(std::to_string(currentScore));
	m_score.setPosition(700.0f, 0.0f);
}

void Hud::update(double dt)
{
	currentScore++;
	m_score.setString(std::to_string(currentScore));
}

void Hud::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_score);
}
