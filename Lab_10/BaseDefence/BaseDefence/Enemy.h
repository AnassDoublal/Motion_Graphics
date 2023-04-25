#pragma once
#include "SFML/Graphics.hpp"
#include "Thor/Vectors.hpp"
#include "Hive.h"
#include "CommandCenter.h"
#include "iostream"
#include "Marker.h"
#include "Pulse.h"
#include "Algorithm.h"
int const ENEMY_AMOUNT = 10;
class Enemy
{
public:
	Enemy() = default;

	sf::Sprite m_enemy;
	/// <summary>
	/// Construct enemy
	/// </summary>
	/// <param name="t_texture">Enemy texture</param>
	Enemy(sf::Texture const&, std::vector<Hive>&, int);
	/// <summary>
	/// Initialize enemy
	/// </summary>
	/// <param name="t_texture">Enemy texture</param>
	void init(sf::Texture const&, std::vector<Hive>&, int);
	/// <summary>
	/// Update enemy
	/// </summary>
	void update(Hive&, double dt);

	/// <summary>
	/// Render enemy
	/// </summary>
	/// <param name=""></param>
	void render(sf::RenderWindow&);
	/// <summary>
	/// Spawn enemy from a hive
	/// </summary>
	/// <param name=""></param>
	void spawnEnemy(Hive&);

	/// <summary>
	/// Give BFS path
	/// </summary>
	void setPath(Algorithm&);

	Hive& getHive();

	void attackCommandCenter(CommandCenter&);

	bool hasReachedWall = false;
	bool firstTimeReachingWall = true;

	sf::Vector2f m_destination;
	bool m_wasScanned = false;

private:
	std::vector<sf::Vector2f> m_positions;
	/// destination of the enemy
	// size of enemy
	sf::IntRect m_rect = { 0, 0, 20, 20 };

	sf::Vector2f const getEnemyCenter();

	Hive* m_hive;

	int nextPos = 0;
};