#include "Game.h"

// Construct game
Game::Game(sf::RenderWindow& t_window)
	:m_window(t_window)
{
	loadTextures();
}
// Run game
void Game::run(sf::Time& timeSinceLastUpdate, sf::Clock& clock, sf::Time& timePerFrame)
{
	processEvents(); // as many as possible
	timeSinceLastUpdate += clock.restart();
	while (timeSinceLastUpdate > timePerFrame)
	{
		timeSinceLastUpdate -= timePerFrame;
		processEvents(); // at least 60 fps
		update(timePerFrame.asMilliseconds()); //60 fps
	}
	render(); // as many as possible
}

// Initialize game
void Game::init()
{
	hudObj = Hud(m_font);
	std::srand(time(NULL));
	// platform position
	sf::Vector2f platformPos[4]
	{
		{600,300},
		{850,300},
		{850,600},
		{600,600}
	};
	for (size_t i = 0; i < MAX_BARRELS; i++)
	{
		barrelObjs.push_back(Toxic(m_barrelTexture, m_explosionTexture, m_barrelPosition[i]));
	}
	for (size_t i = 0; i < 4; i++)
	{
		platformObj[i].init(m_platformTexture, platformPos[i]);
	}
	

	for (size_t i = 0; i < HIVE_AMOUNT; i++)
	{
		hiveObjs.push_back(Hive(m_hiveTexture, i));
	}
	enemyObjs.reserve(2000);

	for (size_t i = 0; i <= WALL_AMOUNT; i++)
	{
		for (size_t j = 0; j <= WALL_AMOUNT; j++)
		{
			if (i < 1 || i > WALL_AMOUNT - 1 || j < 1 || j > WALL_AMOUNT - 1)
			{
				wallObjs.push_back(Wall(m_wallTexture, i, j));
			}
		}
	}
	gridCon.init();
	for (size_t i = 0; i < wallObjs.size(); i++)
	{
		wallObjs[i].m_wallCell = gridCon.getObjId(wallObjs[i].m_wall.getPosition());

		gridCon.grid[wallObjs[i].m_wallCell].setMarked(true);

	}
	for (size_t i = 0; i < ENEMY_AMOUNT; i++)
	{
		algoObjs.push_back(gridCon);
	}
	
	
	commandCenterObj = CommandCenter(m_commandCenterTexture);
	//enemyObjs.reserve(2000);
	for (size_t i = 0; i < ENEMY_AMOUNT; i++)
	{
		int random = std::rand() % 4;
		enemyObjs.push_back(Enemy(m_enemyTexture, hiveObjs, random));
		enemyObjs[i].spawnEnemy(hiveObjs[random]);

		int randomWall = std::rand() % wallObjs.size();
		enemyObjs[i].m_destination = algoObjs[i].grid[wallObjs[randomWall].m_wallCell].m_pos;
		enemyObjs[i].setPath(algoObjs[i]);
	}
	//std::cout << algoObj.getId(wallObjs[0].m_wall.getPosition());

	lightObj.init();

	gameOverText.setFont(m_font);
	gameOverText.setPosition(600, 300);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setCharacterSize(48);

	gameOverBg.setFillColor(sf::Color::Black);
	gameOverBg.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
}

// Update game
void Game::update(double dt)
{
	for (size_t i = 0; i < barrelObjs.size(); i++)
	{
		barrelObjs[i].update(dt);

		for (size_t j = 0; j < playerObj.m_bullet.getBullets().size(); j++)
		{
			if (newCollision.collision(barrelObjs[i].m_barrel, playerObj.m_bullet.getBullets()[j].m_bulletSprite) && barrelObjs[i].m_explosionHappened == false)
			{
				barrelObjs[i].m_explosionHappened = true;
			}
		}
		if (barrelObjs[i].m_explosionHappened == true)
		{
			for (size_t k = 0; k < enemyObjs.size(); k++)
			{
				if (newCollision.collision(barrelObjs[i].m_animatedExplosion, enemyObjs[k].m_enemy))
				{
					// Enemies die when they are hit.
					enemyObjs.erase(enemyObjs.begin() + k);
				}
			}
		}
		if (barrelObjs[i].del == true)
		{

			barrelObjs[i].m_animatedExplosion.setPosition(-100, -100);
			barrelObjs[i].m_barrel.setPosition(-100, -100);
			std::cout << "explo\n";

		}
		
	}
	
	for (size_t i = 0; i < bloodObjs.size(); i++)
	{
		bloodObjs[i].update();
	}
	for (size_t i = 0; i < debrisObjs.size(); i++)
	{
		debrisObjs[i].update();
	}
	for (size_t i = 0; i < HIVE_AMOUNT; i++)
	{
		if (newCollision.collision(playerObj.m_playerSprite, hiveObjs[i].m_hive))
		{
			playerObj.getWall(hiveObjs[i].m_hive, hiveObjs[i].m_hiveSize);
		}
	}
	for (size_t i = 0; i < wallObjs.size(); i++)
	{
		if (newCollision.collision(playerObj.m_playerSprite, wallObjs[i].m_wall))
		{
			playerObj.getWall(wallObjs[i].m_wall, wallObjs[i].m_wallSize);
		}
	}
	if (newCollision.collision(playerObj.m_playerSprite, commandCenterObj.m_commandCenter))
	{
		playerObj.getWall(commandCenterObj.m_commandCenter, commandCenterObj.m_commandCenterSize);
	}
	playerObj.update(dt, m_window);
	for (size_t i = 0; i < MAX_PLATFORMS; i++)
	{
		// if player collides with platform, slow player down
		if (newCollision.collision(playerObj.m_playerSprite, platformObj[i].m_platform))
		{
			playerObj.m_maxVelocity = 1.5;
			bool onPlatform = true;
			platformObj[i].setOnPlatform(onPlatform);

		}
		// if player leaves the platform, speed player up
		if (!newCollision.collision(playerObj.m_playerSprite, platformObj[i].m_platform) && platformObj[i].isOnPlatform())
		{
			playerObj.m_maxVelocity = 3.0;
			bool onPlatform = false;
			platformObj[i].setOnPlatform(onPlatform);
		}
	}
	

	// Pulse collision with the enemies
	for (size_t i = 0; i < enemyObjs.size(); i++)
	{
		if (newCollision.collision(commandCenterObj.pulseObj.m_pulse, enemyObjs[i].m_enemy) && !enemyObjs[i].m_wasScanned)
		{
			enemyObjs[i].m_wasScanned = true;
			commandCenterObj.pulseObj.m_markers.push_back(Marker(enemyObjs[i].m_enemy.getPosition()));
		}
		if (enemyObjs[i].m_wasScanned && !commandCenterObj.pulseObj.showMarkers)
		{
			enemyObjs[i].m_wasScanned = false;
		}
	}
	
	// Update command center

	commandCenterObj.update(dt);

	// Update enemies
	for (size_t i = 0; i < enemyObjs.size(); i++)
	{
		enemyObjs[i].update(enemyObjs[i].getHive(), dt);

		if (enemyObjs[i].hasReachedWall)
		{
			//std::cout << "reached wall with index : " << enemyObjs[i].m_destinationWall << "\n";

			for (size_t j = 0; j < wallObjs.size(); j++)
			{
				if (enemyObjs[i].m_enemy.getPosition().x <= wallObjs[j].m_wall.getPosition().x + 30.0f
				 && enemyObjs[i].m_enemy.getPosition().x >= wallObjs[j].m_wall.getPosition().x - 30.0f
				 && enemyObjs[i].m_enemy.getPosition().y <= wallObjs[j].m_wall.getPosition().y + 30.0f
				 && enemyObjs[i].m_enemy.getPosition().y >= wallObjs[j].m_wall.getPosition().y - 30.0f)
				{
					wallObjs.erase(wallObjs.begin() + j);
				}
			}

			enemyObjs[i].attackCommandCenter(commandCenterObj);
		}

		if (newCollision.collision(enemyObjs[i].m_enemy, commandCenterObj.m_commandCenter))
		{
			gameOverText.setString("      Game Over\nEnemies killed: " + std::to_string(hudObj.currentScore));
			gameOver = true;
		}
	}

	// Bullet and enemy collisions
	for (size_t i = 0; i < playerObj.m_bullet.getBullets().size(); i++)
	{
		for (size_t j = 0; j < enemyObjs.size(); j++)
		{
			if (newCollision.collision(playerObj.m_bullet.getBullets()[i].m_bulletSprite, enemyObjs[j].m_enemy) && playerObj.m_bullet.getBullets()[i].inUse())
			{
				// sets the particles position and color as the position of the enemy and blood
				particleObj.init(enemyObjs[j].m_enemy.getPosition(), red);
				// Enemies die when they are hit.
				enemyObjs.erase(enemyObjs.begin() + j);
				hudObj.update(dt);
				// creates a new particle where the bullet collieded with the enemy
				bloodObjs.push_back(particleObj);
				// sets the bullets to inactive to delete them
				playerObj.m_bullet.getBullets()[i].m_speed = 0;
			}
		}
	}
	// Bullet and wall collisions
	for (size_t i = 0; i < playerObj.m_bullet.getBullets().size(); i++)
	{
		for (size_t j = 0; j < wallObjs.size(); j++)
		{
			if (playerObj.m_bullet.getBullets()[i].inUse())
			{
				for (size_t k = 0; k < MAX_PLATFORMS; k++)
				{
					if (newCollision.collision(playerObj.m_bullet.getBullets()[i].m_bulletSprite, wallObjs[j].m_wall) && !platformObj->isOnPlatform())
					{
						// sets the particles position and color as the position of the enemy and blood
						particleObj.init(wallObjs[j].m_wall.getPosition(), sf::Color::White);
						// creates a new particle where the bullet collieded with the enemy
						debrisObjs.push_back(particleObj);
						// sets the bullets to inactive to delete them
						playerObj.m_bullet.getBullets()[i].m_speed = 0;
					}
				}
				
			}
		}
	}

	lightObj.update(playerObj);

	if (enemyObjs.size() <= 0)
	{
		gameOverText.setString("      Game Over\nEnemies killed: " + std::to_string(ENEMY_AMOUNT));
		gameOver = true;
	}
}

// Render game objects
void Game::render()
{
	for (size_t i = 0; i < HIVE_AMOUNT; i++)
	{
		hiveObjs[i].render(m_window);
	}

	for (size_t i = 0; i < wallObjs.size(); i++)
	{
		wallObjs[i].render(m_window);
	}

	for (size_t i = 0; i < enemyObjs.size(); i++)
	{
		enemyObjs[i].render(m_window);
	}

	for (size_t i = 0; i < bloodObjs.size(); i++)
	{
		bloodObjs[i].render(m_window);
	}
	for (size_t i = 0; i < debrisObjs.size(); i++)
	{
		debrisObjs[i].render(m_window);
	}
	for (size_t i = 0; i < 4; i++)
	{
		platformObj[i].render(m_window);
	}
	m_window.draw(lightObj.m_circle);
	playerObj.render(m_window);
	lightObj.render(m_window);

	hudObj.render(m_window);
	commandCenterObj.render(m_window);

	for (size_t i = 0; i < barrelObjs.size(); i++)
	{
		barrelObjs[i].render(m_window);
	}

	if (gameOver)
	{
		m_window.draw(gameOverBg);
		m_window.draw(gameOverText);
	}
}

// Process events
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

// Process game events
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

// Load all game textures
void Game::loadTextures()
{
	if (!m_hiveTexture.loadFromFile("./resources/images/hive.png"))
	{
		std::cout << "Failed to load hive texture\n";
	}

	if (!m_enemyTexture.loadFromFile("./resources/images/enemy.png"))
	{
		std::cout << "Failed to load enemy texture\n";
	}

	if (!m_wallTexture.loadFromFile("./resources/images/wall.png"))
	{
		std::cout << "Failed to load wall texture\n";
	}

	if (!m_commandCenterTexture.loadFromFile("./resources/images/commandCenter.png"))
	{
		std::cout << "Failed to load command center texture\n";
	}

	if (!m_platformTexture.loadFromFile("./resources/images/platform.png"))
	{
		std::cout << "Failed to load platform texture\n";
	}
	if (!m_barrelTexture.loadFromFile("./resources/images/barrelTNT.png"))
	{
		std::cout << "Failed to load barrel texture\n";
	}
	if (!m_explosionTexture.loadFromFile("./resources/images/explosion.png"))
	{
		std::cout << "Failed to load explosion texture\n";
	}
	if (!m_font.loadFromFile("./resources/fonts/BebasNeue.otf"))
	{
		std::cout << "Failed to load font \n";
	}
}
