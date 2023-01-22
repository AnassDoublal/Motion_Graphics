#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"

void obstacleManager(sf::Sprite& obstacle, int& randObstacle, bool& spawnObstacle)
{
	if (obstacle.getPosition().x < -obstacle.getGlobalBounds().width)
	{
		obstacle.setPosition(20000.0f, 20000.0f);
		randObstacle = rand() % 10;
		spawnObstacle = true;
	}
}

void gameOverCheck(sf::Sprite& player, sf::Sprite obstacle, bool& gameOver)
{
	if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		gameOver = true;
}

int main()
{
	srand(time(NULL));

// Start

	int screenHeight = 200;
	int screenWidth = 800;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Dino");

	sf::Texture texture;
	if (!texture.loadFromFile("dino.png"))
	{
		// Error
	}

	sf::Sprite dino;
	dino.setTexture(texture);
	dino.setTextureRect(sf::IntRect(677, 0, 44, 49));
	dino.setPosition(20.0f, window.getSize().y - dino.getGlobalBounds().height);

	float jumpSpeed = -6.5f;
	bool isGrounded = true;
	bool isDucking = false;
	bool changeJumpDirection = false;

	sf::Sprite ground;
	ground.setTexture(texture);
	ground.setTextureRect(sf::IntRect(2, 53, 802, 15));
	ground.setPosition(.0f, window.getSize().y - ground.getGlobalBounds().height);

	sf::Sprite groundCopy;
	groundCopy = ground;
	groundCopy.setPosition(800.0f, window.getSize().y - groundCopy.getGlobalBounds().height);

	std::vector<sf::Sprite> clouds;

	std::vector<float> cloudPositionsX;

	for (int i = 0; i < 5; i++)
	{
		cloudPositionsX.push_back(.0f);
	}

	cloudPositionsX[0] = 800.0f;
	cloudPositionsX[1] = 1080.0f;
	cloudPositionsX[2] = 1270.0f;
	cloudPositionsX[3] = 1400.0f;
	cloudPositionsX[4] = 1550.0f;

	std::vector<float> cloudPositionsY;

	for (int i = 0; i < 5; i++)
	{
		cloudPositionsY.push_back(.0f);
	}

	cloudPositionsY[0] = 40.0f;
	cloudPositionsY[1] = 20.0f;
	cloudPositionsY[2] = 70.0f;
	cloudPositionsY[3] = 30.0f;
	cloudPositionsY[4] = 30.0f;

	for (int i = 0; i < 5; i++)
	{
		sf::Sprite cloud;
		cloud.setTexture(texture);
		cloud.setTextureRect(sf::IntRect(85, 0, 47, 15));

		clouds.push_back(cloud);
	}

	for (int i = 0; i < 5; i++)
	{
		clouds[i].setPosition(cloudPositionsX[i], cloudPositionsY[i]);
	}

	ground.setTexture(texture);
	ground.setTextureRect(sf::IntRect(2, 53, 802, 15));
	ground.setPosition(.0f, window.getSize().y - ground.getGlobalBounds().height);

	float groundSpeed = -7.5f;
	float maxGroundSpeed = -20.0f;

	int totalElapsed = 0;
	int animationframe = 0;

	int score = 0;
	int scoreFrameIndex = 0;
	sf::Font font;

	if (!font.loadFromFile("font.ttf"))
	{
		// Error
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("00000");
	scoreText.setCharacterSize(12);
	scoreText.setPosition(window.getSize().x - scoreText.getGlobalBounds().width - 30.0f, 20.0f);
	scoreText.setFillColor(sf::Color::Black);

	int highScore = 0;
	sf::Text highScoreText;
	highScoreText.setFont(font);
	highScoreText.setString("HI 00000");
	highScoreText.setCharacterSize(12);
	highScoreText.setPosition(scoreText.getPosition().x - highScoreText.getGlobalBounds().width - 15.0f, scoreText.getPosition().y);
	highScoreText.setFillColor(sf::Color::Black);

	int randObstacle = 0;
	int numSmallCactuses = 0;
	int numBigCactuses = 0;

	sf::Sprite bird;
	bird.setTexture(texture);
	bird.setTextureRect(sf::IntRect(135, 0, 45, 42));
	bird.setPosition(20000.0f, .0f);

	float birdPosYToss = .0f;

	sf::Sprite oneSmallCactus;
	oneSmallCactus.setTexture(texture);
	oneSmallCactus.setTextureRect(sf::IntRect(228, 0, 17, 37));
	oneSmallCactus.setPosition(20000.0f, 20000.0f);

	sf::Sprite twoSmallCactuses;
	twoSmallCactuses.setTexture(texture);
	twoSmallCactuses.setTextureRect(sf::IntRect(228, 0, 34, 37));
	twoSmallCactuses.setPosition(20000.0f, 20000.0f);

	sf::Sprite threeSmallCactuses;
	threeSmallCactuses.setTexture(texture);
	threeSmallCactuses.setTextureRect(sf::IntRect(228, 0, 51, 37));
	threeSmallCactuses.setPosition(20000.0f, 20000.0f);

	sf::Sprite oneBigCactus;
	oneBigCactus.setTexture(texture);
	oneBigCactus.setTextureRect(sf::IntRect(331, 0, 26, 52));
	oneBigCactus.setPosition(20000.0f, 20000.0f);

	sf::Sprite twoBigCactuses;
	twoBigCactuses.setTexture(texture);
	twoBigCactuses.setTextureRect(sf::IntRect(331, 0, 50, 52));
	twoBigCactuses.setPosition(20000.0f, 20000.0f);

	sf::Sprite specialMix;
	specialMix.setTexture(texture);
	specialMix.setTextureRect(sf::IntRect(407, 0, 75, 52));
	specialMix.setPosition(20000.0f, 20000.0f);

	float obstaclePosX = .0f;
	bool spawnObstacle = true;
	int randRespawnPosX = 0;

	int totalElapsedBird = 0;
	int animationframeBird = 0;

	bool gameOver = false;

	sf::Sprite restartBtn;
	restartBtn.setTexture(texture);
	restartBtn.setTextureRect(sf::IntRect(2, 2, 35, 31));
	restartBtn.setPosition(20000.0f, 10000.0f);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(16);
	gameOverText.setString("GAME OVER");
	gameOverText.setFillColor(sf::Color::Black);
	gameOverText.setLetterSpacing(4.0f);
	gameOverText.setPosition(20000.0f, 10000.0f);

	std::ifstream highScoreFileRead("highScore.txt");
	std::string highScoreFileContent;

	while (getline(highScoreFileRead, highScoreFileContent)) {
			highScore = stoi(highScoreFileContent);
		if (highScore < 10)
			highScoreText.setString("HI 0000");
		else if (highScore >= 10 && highScore < 100)
			highScoreText.setString("HI 000");
		else if (highScore >= 100 && highScore < 1000)
			highScoreText.setString("HI 00");
		else if (highScore >= 1000 && highScore < 10000)
			highScoreText.setString("HI 0");
		highScoreText.setString(highScoreText.getString() + highScoreFileContent);
	}
	highScoreFileRead.close();

	std::ofstream highScoreFileWrite("highScore.txt");
	highScoreFileWrite << highScoreFileContent;
	highScoreFileWrite.close();

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Clock clockForFrameRate;

	clockForFrameRate.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		timeSinceLastUpdate += clockForFrameRate.restart();


		if (timeSinceLastUpdate > timePerFrame)
		{
			window.clear(sf::Color(sf::Color::White));

// Update

			if (!gameOver)
			{
				// Score

				scoreFrameIndex++;

				if (scoreFrameIndex > 5)
				{
					score++;
					scoreFrameIndex = 0;
				}
				if (score < 10)
					scoreText.setString("0000");
				else if (score >= 10 && score < 100)
					scoreText.setString("000");
				else if (score >= 100 && score < 1000)
					scoreText.setString("00");
				else if (score >= 1000 && score < 10000)
					scoreText.setString("0");
				scoreText.setString(scoreText.getString() + std::to_string(score));
				scoreText.setPosition(window.getSize().x - scoreText.getGlobalBounds().width - 30.0f, 20.0f);

				// Obstacles

				oneSmallCactus.move(groundSpeed, .0f);
				twoSmallCactuses.move(groundSpeed, .0f);
				threeSmallCactuses.move(groundSpeed, .0f);
				oneBigCactus.move(groundSpeed, .0f);
				twoBigCactuses.move(groundSpeed, .0f);
				specialMix.move(groundSpeed, .0f);
				bird.move(groundSpeed, .0f);

				obstacleManager(oneSmallCactus, randObstacle, spawnObstacle);
				obstacleManager(twoSmallCactuses, randObstacle, spawnObstacle);
				obstacleManager(threeSmallCactuses, randObstacle, spawnObstacle);
				obstacleManager(oneBigCactus, randObstacle, spawnObstacle);
				obstacleManager(twoBigCactuses, randObstacle, spawnObstacle);
				obstacleManager(specialMix, randObstacle, spawnObstacle);
				obstacleManager(bird, randObstacle, spawnObstacle);

				gameOverCheck(dino, oneSmallCactus, gameOver);
				gameOverCheck(dino, twoSmallCactuses, gameOver);
				gameOverCheck(dino, threeSmallCactuses, gameOver);
				gameOverCheck(dino, oneBigCactus, gameOver);
				gameOverCheck(dino, twoBigCactuses, gameOver);
				gameOverCheck(dino, specialMix, gameOver);
				gameOverCheck(dino, bird, gameOver);

				if (spawnObstacle)
				{
					spawnObstacle = false;

					if (randObstacle >= 0 && randObstacle < 4)
					{
						numSmallCactuses = rand() % 3;

						switch (numSmallCactuses)
						{
						case 0:
							oneSmallCactus.setPosition(window.getSize().x, 160.0f);
							break;
						case 1:
							twoSmallCactuses.setPosition(window.getSize().x, 160.0f);
							break;
						case 2:
							threeSmallCactuses.setPosition(window.getSize().x, 160.0f);
							break;
						}
					}
					else if (randObstacle >= 4 && randObstacle < 7)
					{
						numBigCactuses = rand() % 2;

						switch (numBigCactuses)
						{
						case 0:
							oneBigCactus.setPosition(window.getSize().x, 147.0f);
							break;
						case 1:
							twoBigCactuses.setPosition(window.getSize().x, 147.0f);
							break;
						}
					}
					else if (randObstacle >= 7 && randObstacle < 9)
					{
						specialMix.setPosition(window.getSize().x, 145.0f);
					}
					else
					{
						birdPosYToss = rand() % 2;

						if(birdPosYToss == 0)
							bird.setPosition(window.getSize().x, 100.0f);
						else
							bird.setPosition(window.getSize().x, 125.0f);
					}
				}

				// Clouds

				for (int i = 0; i < clouds.size(); i++)
				{
					clouds[i].move(groundSpeed / 10.0f, .0f);

					if (clouds[i].getPosition().x < -clouds[i].getGlobalBounds().width)
					{
						clouds[i].setPosition(cloudPositionsX[i], cloudPositionsY[i]);
					}
				}

				// Ground

				ground.move(groundSpeed, .0f);
				groundCopy.move(groundSpeed, .0f);

				if (ground.getPosition().x < -ground.getGlobalBounds().width)
				{
					ground.setPosition(800.0f, ground.getPosition().y);
				}

				if (groundCopy.getPosition().x < -groundCopy.getGlobalBounds().width)
				{
					groundCopy.setPosition(800.0f, groundCopy.getPosition().y);
				}

				if (score > 0 && score % 100 == 0 && groundSpeed >= maxGroundSpeed)
					groundSpeed -= .1f;

				// Jump

				if (isGrounded)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isDucking)
					{
						isGrounded = false;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						isDucking = true;
						dino.setPosition(dino.getPosition().x, window.getSize().y - dino.getGlobalBounds().height - 5.0f);
					}
					else
					{
						isDucking = false;
						dino.setPosition(dino.getPosition().x, window.getSize().y - dino.getGlobalBounds().height - 5.0f);
					}
				}
				else
				{
					if (dino.getPosition().y <= 40.0f)
					{
						changeJumpDirection = true;
					}

					if (!changeJumpDirection)
					{
						dino.move(.0f, jumpSpeed);
					}
					else
					{
						dino.move(.0f, -jumpSpeed);
					}

					if (dino.getPosition().y >= window.getSize().y - dino.getGlobalBounds().height - 10.0f)
					{
						isGrounded = true;
						changeJumpDirection = false;
					}
				}

				// Animation 

				totalElapsed++;
				if (totalElapsed > 5)
				{
					totalElapsed = 0;
					animationframe++;
					if (animationframe > 1)
					{
						animationframe = 0;
					}
				}

				sf::IntRect rectSourceSprite;
				int row = 0;
				if (!isDucking)
				{
					rectSourceSprite.height = 44;
					rectSourceSprite.width = 43;
					row = animationframe * rectSourceSprite.width;
					rectSourceSprite.left = 766 + row;
					rectSourceSprite.top = 3;
				}
				else
				{
					rectSourceSprite.height = 25;
					rectSourceSprite.width = 58;
					row = animationframe * rectSourceSprite.width;
					rectSourceSprite.left = 942 + row;
					rectSourceSprite.top = 22;
				}
				if (isGrounded)
					dino.setTextureRect(rectSourceSprite);
				else
					dino.setTextureRect(sf::IntRect(678, 3, 43, 44));

				totalElapsedBird++;
				if (totalElapsedBird > 10)
				{
					totalElapsedBird = 0;
					animationframeBird++;
					if (animationframeBird > 1)
					{
						animationframeBird = 0;
					}
				}

				sf::IntRect rectSourceSpriteBird;
				rectSourceSpriteBird.height = 42;
				rectSourceSpriteBird.width = 45;
				row = animationframeBird * rectSourceSpriteBird.width;
				rectSourceSpriteBird.left = 135 + row;
				rectSourceSpriteBird.top = 0;
				bird.setTextureRect(rectSourceSpriteBird);
			}
			else
			{
				dino.setTextureRect(sf::IntRect(854, 3, 41, 44));
				restartBtn.setPosition(window.getSize().x / 2.0f - restartBtn.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f + 20.0f);
				gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 20.0f);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					gameOver = false;

					highScoreFileRead.open("highScore.txt");
					while (getline(highScoreFileRead, highScoreFileContent)) {
						if (score > std::stoi(highScoreFileContent))
							highScore = score;
					}
					highScoreFileRead.close();

					highScoreFileWrite.open("highScore.txt");
					highScoreFileWrite << std::to_string(highScore);
					highScoreFileWrite.close();
					if (highScore < 10)
						highScoreText.setString("HI 0000");
					else if (highScore >= 10 && highScore < 100)
						highScoreText.setString("HI 000");
					else if (highScore >= 100 && highScore < 1000)
						highScoreText.setString("HI 00");
					else if (highScore >= 1000 && highScore < 10000)
						highScoreText.setString("HI 0");

					highScoreFileRead.open("highScore.txt");
					while (getline(highScoreFileRead, highScoreFileContent)) {
						std::cout << std::stoi(highScoreFileContent) << "\n";
						if(std::stoi(highScoreFileContent) <= highScore)
							highScoreText.setString(highScoreText.getString() + std::to_string(highScore));
						else
							highScoreText.setString(highScoreText.getString() + highScoreFileContent);
					}
					highScoreFileRead.close();

					score = 0;
					groundSpeed = -7.5f;
					oneSmallCactus.setPosition(20000.0f, 20000.0f);
					twoSmallCactuses.setPosition(20000.0f, 20000.0f);
					threeSmallCactuses.setPosition(20000.0f, 20000.0f);
					oneBigCactus.setPosition(20000.0f, 20000.0f);
					twoBigCactuses.setPosition(20000.0f, 20000.0f);
					specialMix.setPosition(20000.0f, 20000.0f);
					bird.setPosition(20000.0f, 20000.0f);
					restartBtn.setPosition(20000.0f, 10000.0f);
					randObstacle = rand() % 10;
					spawnObstacle = true;
					gameOverText.setPosition(20000.0f, 10000.0f);
				}
			}

// Draw
			for (int i = 0; i < clouds.size(); i++)
			{
				window.draw(clouds[i]);
			}

			window.draw(ground);
			window.draw(groundCopy);
			window.draw(dino);
			window.draw(scoreText);
			window.draw(highScoreText);
			window.draw(bird);
			window.draw(oneSmallCactus);
			window.draw(twoSmallCactuses);
			window.draw(threeSmallCactuses);
			window.draw(oneBigCactus);
			window.draw(twoBigCactuses);
			window.draw(specialMix);
			window.draw(restartBtn);
			window.draw(gameOverText);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}
