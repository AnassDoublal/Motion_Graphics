#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletCreate.h"
#include "Movement.h"
class Player
{

public:
	// player move speed
	int m_maxVelocity = 3;
	int m_velocity = m_maxVelocity;

	Player();
	/// <summary>
	/// handles rendering the player objects
	/// </summary>
	/// <param name="t_window">display screen</param>
	void render(sf::RenderWindow& t_window);
	/// <summary>
	/// updates the player values
	/// </summary>
	/// <param name="dt"></param>
	void update(double dt, sf::RenderWindow&);
	// player sprite
	sf::Sprite m_playerSprite;
	void getWall(sf::Sprite& t_wall, sf::Vector2f t_size);
	// Bullet initalizer
	BulletCreate m_bullet;
	sf::Texture m_bulletTexture;


private:
	Movement movementObj;
	sf::Vector2f m_previousPlayerPos;
	/// <summary>
	/// inital player values
	/// </summary>
	void init();
	// player Texture
	sf::Texture m_playerTexture;
	// player values
	sf::Vector2f m_pos{700,350};

	sf::IntRect m_playerRect{ 0,0,40,40 };
	void playerSetOrigin();
	double m_rotation = 90;
	const double DASH_TIME = 1000;
	// checks how much time has passed since last dash, initialized based on how often we want to player to dash
	double m_elipsedTime = DASH_TIME;
	/// <summary>
	/// Check which direction the player can dash towards
	/// </summary>
	enum Dash
	{
		DASHNONE	= 0,
		DASHUP		= 1,
		DASHDOWN	= 2,
		DASHLEFT	= 3,
		DASHRIGHT	= 4
	};
	enum Facing
	{
		FACINGNONE = 0,
		FACINGUP = 1,
		FACINGRIGHT = 2,
		FACINGDOWN = 3,
		FACINGLEFT = 4
	};
	Facing faceDir = FACINGNONE;
	void facingDirection();
	/// <summary>
	/// player position changes depending on keypress
	/// </summary>
	void movement();

	// Starting Direction of the dash
	Dash dashDir = DASHNONE;

	/// <summary>
	/// Move the player quickly in the direction of the dash
	/// </summary>
	void dash();
	// Bullet initalizer
	
	sf::Vector2f m_wallPos;
	sf::Vector2f m_wallSize;
	// checks if the player wants to shoot the bullet
	void shootBullet();

	// player rotation based on mouse pos
	void getPlayerRotation(sf::RenderWindow & t_window);

	void wallBounce();
};
