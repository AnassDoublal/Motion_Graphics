#include "BulletCreate.h"

void BulletCreate::create(sf::Texture const& texture, double x, double y, double rotation)
{
	// If no bullets available, simply re-use the next in sequence.
	if (m_bulletContainerFull)
	{
		m_nextAvailable = (m_nextAvailable + 1) % BULLET_AMOUNT_SIZE;
	}
	m_bulletSprites.at(m_nextAvailable).init(texture, x, y, rotation);
}

void BulletCreate::update(double dt, sf::Sprite t_player)
{
	// The number of active projectiles.
	int activeCount = 0;
	// Assume the pool is not full initially.
	m_bulletContainerFull = false;
	for (int i = 0; i < BULLET_AMOUNT_SIZE; i++)
	{
		// If bullets.at(i).update() returns true, then this bullet is onscreen
		if (!m_bulletSprites.at(i).update(dt,t_player))
		{
			// If this bullet has expired, make it the next available.
			m_nextAvailable = i;
		}
		else
		{
			// So we know how many bullets are being used.
			activeCount++;
		}
	}
	// If no bullets available, set a flag.
	if (BULLET_AMOUNT_SIZE == activeCount)
	{
		m_bulletContainerFull = true;
	}
}
/// <summary>
/// renders the bullets
/// </summary>
/// <param name="t_window"></param>
void BulletCreate::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < BULLET_AMOUNT_SIZE; i++)
	{
		// If projectile is active...
		if (m_bulletSprites.at(i).inUse())
		{
			t_window.draw(m_bulletSprites.at(i).m_bulletSprite);
		}
	}
}

std::array<BulletUpdate, 100>& BulletCreate::getBullets()
{
	return m_bulletSprites;
}
