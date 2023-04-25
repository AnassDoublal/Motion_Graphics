#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Hud
{
public:
	Hud() = default;
	Hud(sf::Font&);
	void update(double dt);
	void render(sf::RenderWindow&);
	int currentScore = 0;
private:
	sf::Text m_score;
};