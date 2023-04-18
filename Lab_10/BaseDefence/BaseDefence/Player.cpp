#include "Player.h"
/// <summary>
/// Player Constructor which initializes the player values
/// </summary>
Player::Player()
{
	init();
}

void Player::render(sf::RenderWindow& t_window)
{
	m_bullet.render(t_window);
	t_window.draw(m_playerSprite); // draw player sprite
}

void Player::update(double dt, sf::RenderWindow& t_window)
{
	facingDirection();
	//m_playerSprite.setPosition(m_pos); // change the position of the player
	m_bullet.update(dt, m_playerSprite); // update the bullet
	shootBullet(); // shoot the bullet
	m_elipsedTime += dt;
	if (m_velocity != 0)
	{
		m_velocity = m_maxVelocity;
	movement(); // move the player character
	//std::cout << "velo\n";
	}
	else
	{
		wallBounce();
		//std::cout << "no velo\n";
	}
	if (m_elipsedTime >= DASH_TIME)
	{
	dash();
	m_elipsedTime = 0;
	}
	getPlayerRotation(t_window); // gets the rotation of the player
	// set the rotation to the player sprites roation
	m_playerSprite.setRotation(m_rotation);
}

void Player::getWall(sf::Sprite& t_wall, sf::Vector2f t_size)
{
	m_velocity = 0;
	m_wallPos = t_wall.getPosition();
	m_wallSize = t_size;
}


void Player::init()
{
	if (!m_playerTexture.loadFromFile("./resources/images/playerSprite.png")) // load texture from image
	{
		std::cout << "error loading playersprite\n";
	}
	else
	{
		m_playerSprite.setTexture(m_playerTexture); // set texture to player sprite
		m_playerSprite.setPosition(m_pos); // set player position
		m_playerSprite.setRotation(m_rotation);
		playerSetOrigin();

	}
	if (!m_bulletTexture.loadFromFile("./resources/images/bulletSprite.png"))
	{
		std::cout << "error loading bulletsprite\n";
	}

}
void Player::playerSetOrigin()
{
	sf::Vector2f playerOrigin = m_playerSprite.getPosition();
	sf::Vector2i playerSize = { m_playerRect.width,m_playerRect.height };
	playerOrigin.x = playerSize.x / 2;
	playerOrigin.y = playerSize.y / 2;
	m_playerSprite.setOrigin(playerOrigin);
}
void Player::facingDirection()
{
	if (m_rotation >= 270 - 45 && m_rotation - 360 < 270 + 45)
	{
		faceDir = FACINGUP;
	}
	if (m_rotation >= 360 - 45 && m_rotation < 360 + 45 )
	{
		faceDir = FACINGRIGHT;
	}
	if (m_rotation >= 450 - 45 && m_rotation < 450 + 45)
	{
		faceDir = FACINGDOWN;
	}
	if (m_rotation >= 540 - 45 && m_rotation < 540 + 45)
	{
		faceDir = FACINGLEFT;
	}
}
/// <summary>
/// checks what keyboard key is being pressed
/// changes the player position
/// A Key = Left Movement, D Key = Right Movement, W Key = Up Movement, S Key = Down Movement
/// </summary>
void Player::movement()
{
	// right, left movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_pos.x += m_velocity;
		dashDir = DASHRIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_pos.x -= m_velocity;
		dashDir = DASHLEFT;
	}
	// up, down movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pos.y -= m_velocity;
		dashDir = DASHUP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pos.y += m_velocity;
		dashDir = DASHDOWN;
	}
	m_playerSprite.setPosition(m_pos);
}
/// <summary>
/// When Left Shift is pressed 
/// checks the direction the player wants to dash
/// </summary>
void Player::dash()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		switch (dashDir)
		{
		case Player::DASHNONE:
			break;
		case Player::DASHUP:
			m_pos.y -= 50;
			dashDir = DASHNONE;
			break;
		case Player::DASHDOWN:
			m_pos.y += 50;
			dashDir = DASHNONE;
			break;
		case Player::DASHLEFT:
			m_pos.x -= 50;
			dashDir = DASHNONE;
			break;
		case Player::DASHRIGHT:
			m_pos.x += 50;
			dashDir = DASHNONE;
			break;
		default:
			break;
		}
	}
}
/// <summary>
/// shoots the bullet using the left mouse click
/// </summary>
void Player::shootBullet()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// creates the bullet at player pos
		m_pos = movementObj.recoilControl(m_pos, faceDir);

		m_bullet.create(m_bulletTexture, m_playerSprite.getPosition().x, m_playerSprite.getPosition().y, m_playerSprite.getRotation());
	}
}

void Player::getPlayerRotation(sf::RenderWindow& t_window)
{
	// mouse position based on the display screen
	sf::Vector2i mousePos = sf::Mouse::getPosition(t_window);
	// position at which the player head is
	sf::Vector2f headPos = m_playerSprite.getPosition();

	// subtraction of the mouse and the player head coordinates
	float dx = mousePos.x - headPos.x;
	float dy = mousePos.y - headPos.y;

	// angle in radians taken from between the two vectors
	auto angle = atan2(dx, dy);
	// angle conversion to degrees
	angle = angle * (180 / thor::Pi);
	// angle normalised to 0 starting at the right hand side
	angle -= 90;
	// angle pointing the correct direction
	angle -= 360;
	// angle given in positive rather in negative
	angle = abs(angle);
	// set the rotation to the angle
	m_rotation = angle;
	std::cout << angle << std::endl;
}
void Player::wallBounce()
{
	m_velocity = m_maxVelocity;
	//right to left
	if (m_pos.x >= m_wallPos.x)
	{
		m_pos.x = m_pos.x +m_velocity;
	}
	//top to bottom
	if (m_pos.y >= m_wallPos.y)
	{
		m_pos.y = m_pos.y + m_velocity;
	}
	//  left to right
	if (m_pos.x < m_wallPos.x)
	{
		m_pos.x = m_pos.x - m_velocity;
	}
	//bottom to top
	if (m_pos.y < m_wallPos.y)
	{
		m_pos.y = m_pos.y - m_velocity;
	}
	//std::cout << m_pos.x << m_wallPos.x;
	m_playerSprite.setPosition(m_pos);
};
