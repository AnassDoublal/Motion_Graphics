#pragma once
#include "SFML/Graphics.hpp"
#include "Pulse.h"

class CommandCenter
{
public:
	/// <summary>
	/// Command center default constructor
	/// </summary>
	CommandCenter();
	/// <summary>
	/// Construct command center
	/// </summary>
	/// <param name="t_texture">Command center texture</param>
	CommandCenter(sf::Texture&);
	/// <summary>
	/// Initialize command center
	/// </summary>
	/// <param name="t_texture">Command center texture</param>
	void init(sf::Texture&);
	/// <summary>
	/// Update command center
	/// </summary>
	void update(double dt);
	/// <summary>
	/// Render command center
	/// </summary>
	/// <param name="t_window">Game window</param>
	/*sf::Vector2f m_enemyPos[ENEMY_AMOUNT];*/
	void render(sf::RenderWindow&);
	sf::Sprite m_commandCenter;
	sf::Vector2f m_commandCenterSize;
	Pulse pulseObj;
	
private:
	sf::IntRect m_rect = { 0, 0, 60, 60 };
	sf::Vector2f const getCommandCenterCenter();
};