#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Hive.h"
#include "Enemy.h"
#include "Wall.h"
#include "CommandCenter.h"
#include "Grid.h"
#include "Collision.h"
#include "Algorithm.h"
#include "ParticleSystem.h"
#include "Marker.h"
#include <iostream>
#include "Platform.h"
#include "Toxic.h"
#include "Light.h"
#include "Hud.h"

class Game
{
public:
	Game(sf::RenderWindow&);
	void run(sf::Time&, sf::Clock&, sf::Time&);
	void init();

protected:
	static const int MAX_PLATFORMS = 4;
	// Object constructors
	Hud hudObj;
	Player playerObj;
	std::vector<Hive> hiveObjs;
	std::vector<Enemy> enemyObjs;
	std::vector<Wall> wallObjs;
	CommandCenter commandCenterObj;
	Grid gridObj;
	Collisions newCollision;
	Algorithm gridCon;
	std::vector<Algorithm> algoObjs;
	ParticleSystem particleObj;
	std::vector<ParticleSystem>bloodObjs;
	std::vector<ParticleSystem>debrisObjs;
	Platform  platformObj[MAX_PLATFORMS];
	std::vector<Toxic> barrelObjs;
	Light lightObj;

	static const int MAX_BARRELS = 4;
	sf::Vector2f m_barrelPosition[MAX_BARRELS]
	{
		{300,300},
		{1150,300},
		{350,600},
		{1100,600}
	};
	/// <summary>
	/// update the game events
	/// </summary>
	/// <param name="dt">delta time</param>
	void update(double dt);
	/// <summary>
	/// render the game
	/// </summary>
	void render();
	/// <summary>
	/// check what event happened
	/// </summary>
	void processEvents();
	/// <summary>
	/// process game events
	/// </summary>
	/// <param name=""></param>
	void processGameEvents(sf::Event&);
	/// <summary>
	/// game window
	/// </summary>
	sf::RenderWindow& m_window;
	
	/// <summary>
	/// load textures
	/// </summary>
	void loadTextures();
	sf::Color grey{ 128,128,128 };
	sf::Color red{ 255,0,0 };
	// Game textures
	sf::Texture m_platformTexture;
	sf::Texture m_hiveTexture;
	sf::Texture m_enemyTexture;
	sf::Texture m_wallTexture;
	sf::Texture m_commandCenterTexture;
	sf::Texture m_barrelTexture;
	sf::Texture m_explosionTexture;
	sf::Font m_font;
};