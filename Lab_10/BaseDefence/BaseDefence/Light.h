#pragma once
#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"
#include "SFML/Graphics.hpp"
#include "Player.h"

class Light
{
public:
	/// <summary>
	/// Light initialization
	/// </summary>
	void init();
	/// <summary>
	/// Light update
	/// </summary>
	/// <param name="t_player">Player reference</param>
	void update(Player&);
	/// <summary>
	/// Light render
	/// </summary>
	/// <param name="t_window">Game window</param>
	void render(sf::RenderWindow&);
	sf::CircleShape m_circle;
private:
	candle::RadialLight m_light;
};