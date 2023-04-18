#include "Enemy.h"

// Construct enemy
Enemy::Enemy(sf::Texture const& t_texture, std::vector<Hive>& t_hiveObjs, int t_index)
{
	init(t_texture, t_hiveObjs, t_index);
}

// Initialize enemy
void Enemy::init(sf::Texture const& t_texture, std::vector<Hive>& t_hiveObjs, int t_index)
{
	m_enemy.setTexture(t_texture);
	
	/*switch (t_index)
	{
		case 0: case 3:
			m_destination = { static_cast<float>(std::rand() % 600), static_cast<float>(std::rand() % 900) };
			break;
		case 1: case 2:
			m_destination = { static_cast<float>(std::rand() % 800 + 640), static_cast<float>(std::rand() % 900) };
			break;
	}*/
	m_enemy.setOrigin(getEnemyCenter());
	m_enemy.setTextureRect(m_rect);
	m_hive = &t_hiveObjs[t_index];

}

void Enemy::setPath(Algorithm& t_algorithm)
{
	int hiveID = t_algorithm.getObjId(m_hive->m_hive.getPosition());
	int destinationID = t_algorithm.getObjId(m_destination);
	t_algorithm.grid[destinationID].setMarked(false);

	std::vector<sf::Vector2f> bfs = t_algorithm.breadthFirst(t_algorithm.grid, hiveID, destinationID);

	for (size_t i = 0; i < bfs.size(); i++)
	{
		m_positions.push_back(bfs[i]);
	}

	nextPos = m_positions.size() - 2;
}

// Update enemy
void Enemy::update(Hive& t_hive, double dt)
{
	if (nextPos > 0)
	{
		m_enemy.move(thor::unitVector(m_positions[nextPos] - m_enemy.getPosition()));
	}

	if (m_enemy.getPosition().x + 1.0f > m_positions[nextPos].x
		&& m_enemy.getPosition().y + 1.0f > m_positions[nextPos].y)
	{
		if (nextPos > 0)
		{
			nextPos--;
		}
	}
}

// Render enemy
void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_enemy);
}

// Get center of enemy
sf::Vector2f const Enemy::getEnemyCenter()
{
	sf::Vector2f origin;
	origin.x = m_rect.width / 2.0f;
	origin.y = m_rect.height / 2.0f;
	return origin;
}
// Spawn enemy from a hive
void Enemy::spawnEnemy(Hive& t_hive)
{
	m_enemy.setPosition(t_hive.m_hive.getPosition());
}

Hive& Enemy::getHive()
{
	return *m_hive;
}
