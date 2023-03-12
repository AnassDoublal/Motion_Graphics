#include "LevelEditor.h"

void LevelEditor::init(sf::Font& font, sf::RenderWindow& window, sf::View& view)
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

	platformTile.setFillColor(sf::Color::Red);
	platformTile.setSize(sf::Vector2f(30.0f, 30.0f));
	platformTile.setPosition(50.0f, window.getSize().y / 6.0f);

	obstacleTile.setFillColor(sf::Color::Blue);
	obstacleTile.setSize(sf::Vector2f(30.0f, 30.0f));
	obstacleTile.setPosition(50.0f, window.getSize().y / 6.0f * 2.0f);

	jumpPadTile.setFillColor(sf::Color::Green);
	jumpPadTile.setSize(sf::Vector2f(30.0f, 30.0f));
	jumpPadTile.setPosition(50.0f, window.getSize().y / 6.0f * 3.0f);

	gravitySwitchTile.setFillColor(sf::Color::Magenta);
	gravitySwitchTile.setSize(sf::Vector2f(30.0f, 30.0f));
	gravitySwitchTile.setPosition(50.0f, window.getSize().y / 6.0f * 4.0f);

	finishLineTile.setFillColor(sf::Color::White);
	finishLineTile.setSize(sf::Vector2f(30.0f, 30.0f));
	finishLineTile.setPosition(50.0f, window.getSize().y / 6.0f * 5.0f);

	activeTile.setSize(sf::Vector2f(1.0f, 1.0f));
	activeTile.setFillColor(sf::Color::Color(0, 0, 0, 0));

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

	finishLineText.setFont(font);
	finishLineText.setFillColor(sf::Color::White);
	finishLineText.setCharacterSize(16);
	finishLineText.setPosition(finishLineTile.getPosition().x + finishLineTile.getGlobalBounds().width + 5.0f, finishLineTile.getPosition().y);
	finishLineText.setString("Finish line");

	view.setCenter(window.getPosition().x, window.getPosition().y);

	initialViewX = window.getPosition().x;
}

void LevelEditor::update(sf::RenderWindow& window)
{
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
		else if (finishLineTile.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			activeTile = finishLineTile;
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
				if (activeTile.getSize().x > 1.0f)
					drawnTiles.push_back(activeTile);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		for (size_t i = 0; i < drawnTiles.size(); i++)
		{
			if (drawnTiles[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				drawnTiles.erase(drawnTiles.begin() + i);
			}
		}
	}

	if(drawnTiles.size() == .0f)
		isTileOccupied = false;

	std::cout << "Number of drawn tiles : " << drawnTiles.size() << "\n";
}

void LevelEditor::controlView(sf::View& view)
{
	viewCoolDown++;

	if (viewCoolDown > 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view.move(viewSpeed, .0f);

			for (int i = 0; i < grid.size(); i++)
			{
				grid[i].move(viewSpeed, .0f);
			}

			platformTile.move(viewSpeed, .0f);
			obstacleTile.move(viewSpeed, .0f);
			jumpPadTile.move(viewSpeed, .0f);
			gravitySwitchTile.move(viewSpeed, .0f);
			finishLineTile.move(viewSpeed, .0f);

			platformText.move(viewSpeed, .0f);
			obstacleText.move(viewSpeed, .0f);
			jumpPadText.move(viewSpeed, .0f);
			gravitySwitchText.move(viewSpeed, .0f);
			finishLineText.move(viewSpeed, .0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && view.getCenter().x > initialViewX - 5 * 30)
		{
			view.move(-viewSpeed, .0f);

			for (int i = 0; i < grid.size(); i++)
			{
				grid[i].move(-viewSpeed, .0f);
			}

			platformTile.move(-viewSpeed, .0f);
			obstacleTile.move(-viewSpeed, .0f);
			jumpPadTile.move(-viewSpeed, .0f);
			gravitySwitchTile.move(-viewSpeed, .0f);
			finishLineTile.move(-viewSpeed, .0f);

			platformText.move(-viewSpeed, .0f);
			obstacleText.move(-viewSpeed, .0f);
			jumpPadText.move(-viewSpeed, .0f);
			gravitySwitchText.move(-viewSpeed, .0f);
			finishLineText.move(-viewSpeed, .0f);
		}

		viewCoolDown = 0;
	}
}

std::vector<std::vector<int>> LevelEditor::generateLevel(sf::RenderWindow& window)
{
	std::vector<std::vector<int>> levelData(20);

	for (int i = 0; i < 100; i++)
	{
		levelData.push_back(std::vector<int>());

		for (int j = 0; j < 20; j++)
		{
			levelData[i].push_back(0);
		}
	}
	
	/*int** levelData = new int* [55];

	for (int i = 0; i < 55; i++) {

		levelData[i] = new int[20];

		for (int j = 0; j < 20; j++) {
			levelData[i][j] = 0;
		}

	}*/

	for (size_t i = 0; i < window.getSize().x * 3; i += 30)
	{
		for (size_t j = 0; j < window.getSize().y * 3; j += 30)
		{
			for (size_t k = 0; k < drawnTiles.size(); k++)
			{
				if(static_cast<int>(drawnTiles[k].getPosition().x) == i && static_cast<int>(drawnTiles[k].getPosition().y) == j)
				{	
					//std::cout << "TILE ON COORDINATES : " << i << " / " << j << "\n";

					if (drawnTiles[k].getFillColor() == sf::Color::Red)
					{
						levelData[i / 30][j / 30] = 1;
					}
					else if (drawnTiles[k].getFillColor() == sf::Color::Blue)
					{
						levelData[i / 30][j / 30] = 2;
					}
					else if (drawnTiles[k].getFillColor() == sf::Color::Green)
					{
						levelData[i / 30][j / 30] = 4;
					}
					else if (drawnTiles[k].getFillColor() == sf::Color::Magenta)
					{
						levelData[i / 30][j / 30] = 5;
					}
					else if (drawnTiles[k].getFillColor() == sf::Color::White)
					{
						levelData[i / 30][j / 30] = 3;
					}
					else if (drawnTiles[k].getFillColor() == sf::Color::Black)
					{
						levelData[i / 30][j / 30] = 0;
					}
				}
			}
		}
	}

	return levelData;
}

void LevelEditor::render(sf::RenderWindow& window)
{
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
	window.draw(finishLineTile);

	window.draw(platformText);
	window.draw(obstacleText);
	window.draw(jumpPadText);
	window.draw(gravitySwitchText);
	window.draw(finishLineText);
}
