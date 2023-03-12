// platform game.....
// Author :Noel O' Hara

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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
#include "LevelEditor.h"
#include "GameState.h"

class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;

	sf::RectangleShape playerShape;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	static const int numRows = 55;
	static const int numCols = 20;
	std::vector<std::vector<int>> levelData = { {} };
	/*int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 } };*/

	std::vector<std::vector<sf::RectangleShape>> level = { {} };

	sf::Font font;
	sf::Text levelCompleteText;

	sf::RectangleShape tileBg;

	bool levelComplete = false;
	bool switchGravity;

	LevelEditor levelEditor;

	GameState gameState = GameState::EDITOR;

	sf::Vector2i initialViewPos;

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Level Editor");
	}

	void awake()
	{
		initialViewPos = window.getPosition();

		for (int i = 0; i < 100; i++)
		{
			levelData.push_back(std::vector<int>());

			for (int j = 0; j < numCols; j++)
			{
				levelData[i].push_back(0);
			}
		}

		for (int i = 0; i < 100; i++)
		{
			level.push_back(std::vector<sf::RectangleShape>());

			for (int j = 0; j < numCols; j++)
			{
				level[i].push_back(sf::RectangleShape());
			}
		}
	}

	void init()
	{
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);
		playerShape.setFillColor(sf::Color::Yellow);

		switchGravity = false;

		levelCompleteText.setFont(font);
		levelCompleteText.setCharacterSize(48);
		levelCompleteText.setFillColor(sf::Color::White);
		levelCompleteText.setString(" LEVEL COMPLETE!\nPress Space to restart");
		levelCompleteText.setPosition(window.getSize().x / 2.0f - 100.0f, window.getSize().y / 2.0f - levelCompleteText.getGlobalBounds().height / 2.0f);

		if (!font.loadFromFile("arial.ttf"))
		{
			// Error
		}

		if(gameState == GameState::EDITOR)
			levelEditor.init(font, window, view);
		else
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					if (levelData[row][col] == 1)
					{
						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);
						level[row][col].setFillColor(sf::Color::Red);
					}
					if (levelData[row][col] == 0)
					{

						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);
						level[row][col].setFillColor(sf::Color::Black);
					}
					if (levelData[row][col] == 2)
					{
						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);

						level[row][col].setFillColor(sf::Color::Blue);

					}
					if (levelData[row][col] == 3)
					{
						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);

						level[row][col].setFillColor(sf::Color::White);

					}
					if (levelData[row][col] == 4)
					{
						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);

						level[row][col].setFillColor(sf::Color::Green);

					}
					if (levelData[row][col] == 5)
					{
						level[row][col].setSize(sf::Vector2f(30, 30));
						level[row][col].setPosition(row * 30, col * 30);

						level[row][col].setFillColor(sf::Color::Magenta);

					}

				}
				std::cout << std::endl;
			}
		}

		view = window.getDefaultView();
	}
	void run()
	{
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();

			if (timeSinceLastUpdate > timePerFrame)
			{
				if (gameState == GameState::EDITOR)
				{
					levelEditor.update(window);
					levelEditor.controlView(view);
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						view.setCenter(initialViewPos.x - 160.0f, initialViewPos.y + 60.0f);

						for (size_t i = 0; i < numRows; i++)
						{
							for (size_t j = 0; j < numCols; j++)
							{
								levelData[i][j] = levelEditor.generateLevel(window)[i][j];
								
								/*tileBg.setFillColor(sf::Color::White);
								tileBg.setSize(sf::Vector2f(200.0f, window.getSize().y));*/

								for (int row = 0; row < numRows; row++)
								{
									for (int col = 0; col < numCols; col++)
									{

										if (levelData[row][col] == 1)
										{

											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);
											level[row][col].setFillColor(sf::Color::Red);
										}
										if (levelData[row][col] == 0)
										{

											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);
											level[row][col].setFillColor(sf::Color::Black);
										}
										if (levelData[row][col] == 2)
										{
											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);

											level[row][col].setFillColor(sf::Color::Blue);

										}
										if (levelData[row][col] == 3)
										{
											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);

											level[row][col].setFillColor(sf::Color::White);

										}
										if (levelData[row][col] == 4)
										{
											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);

											level[row][col].setFillColor(sf::Color::Green);

										}
										if (levelData[row][col] == 5)
										{
											level[row][col].setSize(sf::Vector2f(30, 30));
											level[row][col].setPosition(row * 30, col * 30);

											level[row][col].setFillColor(sf::Color::Magenta);

										}

									}
									std::cout << std::endl;
								}
							}
						}
						
						gameState = GameState::GAME;
					}

					window.setView(view);
				}
				
				else
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					{
						gameState = GameState::EDITOR;
					}

					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (!levelComplete)
								level[row][col].move(-3.7, 0);
						}

					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
					{
						if (!levelComplete)
							velocityY = -11.8;
						else
						{
							levelComplete = false;
							init();
						}
					}

					gravity = 0.6;

					if (!switchGravity)
					{
						velocityY = velocityY + gravity;
						playerShape.move(0, velocityY);
					}
					else
					{
						velocityY = velocityY + gravity;
						playerShape.move(0, -velocityY);
					}


					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (!switchGravity)
							{
								if (velocityY >= 0)
								{
									if (levelData[row][col] == 1)
									{
										if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
										{
											if (playerShape.getPosition().y < level[row][col].getPosition().y)
											{
												gravity = 0;
												velocityY = 0;
												playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
												playerShape.move(0, -playerShape.getGlobalBounds().height);
												break;
											}
											else {
												init();
											}
										}


									}

								}
								if (velocityY < 0)
								{
									if (levelData[row][col] == 1)
									{
										if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
										{
											init();
										}

									}

								}
							}
							else
							{
								if (-velocityY < 0)
								{

									if (levelData[row][col] == 1)
									{
										if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
										{
											if (playerShape.getPosition().y > level[row][col].getPosition().y)
											{
												gravity = 0;
												velocityY = 0;
												playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y + level[row][col].getGlobalBounds().height);
												break;
											}
											else {
												init();
											}
										}


									}

								}
								if (-velocityY >= 0)
								{
									if (levelData[row][col] == 1)
									{
										if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
										{
											init();
										}

									}

								}
							}

							if (levelData[row][col] == 2)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}
							}
							if (levelData[row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									levelComplete = true;
								}
							}
							if (levelData[row][col] == 4)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									velocityY = -15.8;
								}
							}
							if (levelData[row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (!switchGravity)
										switchGravity = true;
									else
										switchGravity = false;
								}
							}
						}
					}

					if (playerShape.getPosition().y > 600 || playerShape.getPosition().y < 0)
					{
						init();
					}
				}

				window.clear();

				if(gameState == GameState::EDITOR)
					levelEditor.render(window);
				else
				{
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							window.draw(level[row][col]);
						}
					}

					if (levelComplete)
						window.draw(levelCompleteText);

					window.draw(playerShape);

					//window.draw(tileBg);
				}

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{


	Game game;

	game.awake();
	game.init();

	game.run();



	return 0;
}
