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
	int levelData[numRows][numCols] = { {} };
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

	sf::RectangleShape level[numRows][numCols];

	sf::RectangleShape platformTile;
	sf::RectangleShape obstacleTile;
	sf::RectangleShape jumpPadTile;
	sf::RectangleShape gravitySwitchTile;

	sf::Font font;
	sf::Text levelCompleteText;

	sf::Text platformText;
	sf::Text obstacleText;
	sf::Text jumpPadText;
	sf::Text gravitySwitchText;

	std::vector<sf::RectangleShape> grid;
	float gridRectX = .0f;
	float gridRectY = .0f;

	sf::RectangleShape tileBg;

	sf::RectangleShape activeTile;
	std::vector<sf::RectangleShape> drawnTiles;
	bool isTileOccupied = false;

	bool levelComplete = false;
	bool switchGravity;

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Level Editor");
	}

	void init()
	{
		for (int i = 0; i < window.getSize().x / 32.0f + 32.0f; i++)
		{
			for (int j = 0; j < window.getSize().y / 32.0f + 32.0f; j++)
			{
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(30.0f, 30.0f));
				rect.setFillColor(sf::Color::Color(0, 0, 0, 0));
				rect.setOutlineThickness(.5);
				rect.setOutlineColor(sf::Color::Color(255, 255, 255, 127));
				rect.setPosition(gridRectX, gridRectY);
				gridRectX += 30.0f;

				if (gridRectX >= window.getSize().x)
				{
					gridRectX = .0f;
					gridRectY += 30.0f;
				}

				grid.push_back(rect);
			}
		}

		tileBg.setFillColor(sf::Color::White);
		tileBg.setSize(sf::Vector2f(200.0f, window.getSize().y));

		platformTile.setFillColor(sf::Color::Red);
		platformTile.setSize(sf::Vector2f(30.0f, 30.0f));
		platformTile.setPosition(50.0f, window.getSize().y / 5.0f);

		obstacleTile.setFillColor(sf::Color::Blue);
		obstacleTile.setSize(sf::Vector2f(30.0f, 30.0f));
		obstacleTile.setPosition(50.0f, window.getSize().y / 5.0f * 2.0f);

		jumpPadTile.setFillColor(sf::Color::Green);
		jumpPadTile.setSize(sf::Vector2f(30.0f, 30.0f));
		jumpPadTile.setPosition(50.0f, window.getSize().y / 5.0f * 3.0f);

		gravitySwitchTile.setFillColor(sf::Color::Magenta);
		gravitySwitchTile.setSize(sf::Vector2f(30.0f, 30.0f));
		gravitySwitchTile.setPosition(50.0f, window.getSize().y / 5.0f * 4.0f);

		activeTile.setSize(sf::Vector2f(1.0f, 1.0f));
		activeTile.setFillColor(sf::Color::Color(0, 0, 0, 0));

		if (!font.loadFromFile("arial.ttf"))
		{
			// Error
		}
		
		platformText.setFont(font);
		platformText.setFillColor(sf::Color::White);
		platformText.setCharacterSize(16);
		platformText.setPosition(platformTile.getPosition().x + platformTile.getGlobalBounds().width + 5.0f, platformTile.getPosition().y);
		platformText.setString("Platform");

		obstacleText.setFont(font);
		obstacleText.setFillColor(sf::Color::White);
		obstacleText.setCharacterSize(16);
		obstacleText.setPosition(obstacleTile.getPosition().x + obstacleTile.getGlobalBounds().width + 5.0f, obstacleTile.getPosition().y);
		obstacleText.setString("Obstacle");

		jumpPadText.setFont(font);
		jumpPadText.setFillColor(sf::Color::White);
		jumpPadText.setCharacterSize(16);
		jumpPadText.setPosition(jumpPadTile.getPosition().x + jumpPadTile.getGlobalBounds().width + 5.0f, jumpPadTile.getPosition().y);
		jumpPadText.setString("Jump Pad");

		gravitySwitchText.setFont(font);
		gravitySwitchText.setFillColor(sf::Color::White);
		gravitySwitchText.setCharacterSize(16);
		gravitySwitchText.setPosition(gravitySwitchTile.getPosition().x + gravitySwitchTile.getGlobalBounds().width + 5.0f, gravitySwitchTile.getPosition().y);
		gravitySwitchText.setString("Gravity Switch");


		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);
		playerShape.setFillColor(sf::Color::Yellow);

		switchGravity = false;

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Blue);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::White);

				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(30, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Green);

				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(30, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Magenta);

				}

			}
			std::cout << std::endl;
		}

		levelCompleteText.setFont(font);
		levelCompleteText.setCharacterSize(48);
		levelCompleteText.setFillColor(sf::Color::White);
		levelCompleteText.setString(" LEVEL COMPLETE!\nPress Space to restart");
		levelCompleteText.setPosition(window.getSize().x / 2.0f - 100.0f, window.getSize().y / 2.0f - levelCompleteText.getGlobalBounds().height / 2.0f);
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

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if(!levelComplete)
							level[row][col].move(-3.7, 0);
					}

				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (platformTile.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						activeTile = platformTile;
					}
					else if (obstacleTile.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						activeTile = obstacleTile;
					}
					else if (jumpPadTile.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						activeTile = jumpPadTile;
					}
					else if (gravitySwitchTile.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						activeTile = gravitySwitchTile;
					}
					else
					{
						activeTile.setPosition(
							window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - (static_cast<int>(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x) % static_cast<int>(activeTile.getSize().x)),
							window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - (static_cast<int>(window.mapPixelToCoords(sf::Mouse::getPosition(window)).y) % static_cast<int>(activeTile.getSize().y))
						);

						for (int i = 0; i < drawnTiles.size(); i++)
						{
							if (static_cast<int>(activeTile.getPosition().x) - static_cast<int>(activeTile.getPosition().x) % static_cast<int>(activeTile.getSize().x) == static_cast<int>(drawnTiles[i].getPosition().x) - static_cast<int>(drawnTiles[i].getPosition().x) % static_cast<int>(drawnTiles[i].getSize().x)
								&& static_cast<int>(activeTile.getPosition().y) - static_cast<int>(activeTile.getPosition().y) % static_cast<int>(activeTile.getSize().y) == static_cast<int>(drawnTiles[i].getPosition().y) - static_cast<int>(drawnTiles[i].getPosition().y) % static_cast<int>(drawnTiles[i].getSize().y))
							{
								isTileOccupied = true;
							}
							else
								isTileOccupied = false;
						}

						if (!isTileOccupied)
						{
							if(activeTile.getSize().x > 1.0f)
								drawnTiles.push_back(activeTile);
						}
					}
				}

				std::cout << "Number of drawn tiles : " << drawnTiles.size() << "\n";

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

				gravity = 0.0;

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
								if(!switchGravity)
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

				window.clear();

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);

					}
				}

				if(levelComplete)
					window.draw(levelCompleteText);

				//window.draw(playerShape);

				//window.draw(tileBg);

				for (int i = 0; i < grid.size(); i++)
				{
					window.draw(grid[i]);
				}

				for (int i = 0; i < drawnTiles.size(); i++)
				{
					window.draw(drawnTiles[i]);
				}

				window.draw(platformTile);
				window.draw(obstacleTile);
				window.draw(jumpPadTile);
				window.draw(gravitySwitchTile);

				window.draw(platformText);
				window.draw(obstacleText);
				window.draw(jumpPadText);
				window.draw(gravitySwitchText);

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{


	Game game;


	game.init();

	game.run();



	return 0;
}
