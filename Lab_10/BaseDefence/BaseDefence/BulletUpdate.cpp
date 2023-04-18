#include "BulletCreate.h"

void BulletUpdate::init(sf::Texture const& texture, double x, double y, double rotation)
{
	m_bulletSprite.setTexture(texture);
	m_bulletSprite.setTextureRect(m_bulletRect);
	m_bulletSprite.setOrigin(m_bulletRect.width / 2.0, m_bulletRect.height / 2.0);
	m_bulletSprite.setPosition(x, y);
	m_bulletSprite.setRotation(rotation);
	m_speed = MAX_SPEED;
}

bool BulletUpdate::update(double dt, sf::Sprite t_player)
{
	if (!inUse())
	{
		// if the bullet isnt moving then dont do anything
		return false;
	}
	sf::Vector2f position = m_bulletSprite.getPosition(); // get the position of the bullet
	sf::Vector2f newPos(position.x + std::cos(MathUtility::DEG_TO_RAD * m_bulletSprite.getRotation()) * m_speed * (dt / 1000),
		position.y + std::sin(MathUtility::DEG_TO_RAD * m_bulletSprite.getRotation()) * m_speed * (dt / 1000));

	m_bulletSprite.setPosition(newPos.x, newPos.y); // set the position of the bullet
	// if the bullet isnt on screen then set the speed of the bullet to 0
	if (!isOnScreen(newPos))
	{
		m_speed = 0;
	}
	else
	{
	}
	return m_speed == MAX_SPEED;
}

bool BulletUpdate::inUse() const
{
    // if the bullet isnt moving then it is not in use
    return m_speed == MAX_SPEED;
}

/// <summary>
/// check if the bullet is on screen
/// </summary>
/// <param name="position">the bullets position</param>
/// <returns></returns>
bool BulletUpdate::isOnScreen(sf::Vector2f position) const
{
	return position.x - m_bulletRect.width / 2 > 0.f
		&& position.x + m_bulletRect.width / 2 < 1440
		&& position.y - m_bulletRect.height / 2 > 0.f
		&& position.y + m_bulletRect.height / 2 < 900;
}