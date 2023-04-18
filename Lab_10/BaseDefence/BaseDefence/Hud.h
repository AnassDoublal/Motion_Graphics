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
private:
	sf::Text m_score;
	int currentScore = 0;
};