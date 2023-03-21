#include "Level.h"

void Level::init()
{
	std::srand(time(NULL));

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
			{
				levelData[i][j] = 1;
			}
			else
			{
				int random = std::rand() % 10;

				if(random >= 0 && random <= 2)
					levelData[i][j] = 1;
				else
					levelData[i][j] = 0;
			}

			switch (levelData[i][j])
			{
				case 0:
					level[i][j].setFillColor(sf::Color::Color(38, 70, 83));
					break;
				case 1:
					level[i][j].setFillColor(sf::Color::Color(42, 157, 143));
					break;
			}

			level[i][j].setSize(sf::Vector2f(50, 50));
			level[i][j].setPosition(tileWidth * j, tileHeight * i);
		}
	}

	coins->loadTexture();

	for (size_t i = 0; i < sizeof(coins) / sizeof(Coin); i++)
	{
		coins[i].init();

		int random = std::rand() % (rows * cols);
		int coinCol = random % cols;
		int coinRow = random / rows;

		while (coinCol == level[coinRow][coinCol].getPosition().x / tileWidth && coinRow == level[coinRow][coinCol].getPosition().y / tileHeight && level[coinRow][coinCol].getFillColor() == sf::Color::Color(42, 157, 143))
		{
			random = std::rand() % (rows * cols);
			coinCol = random % cols;
			coinRow = random / rows;
		}

		coins[i].getCoin().setPosition(tileWidth * coinCol, tileHeight * coinRow);
	}
}

void Level::update()
{
	/*for (auto& coin : coins)
	{
		coin.update();
	}*/
}

void Level::render(sf::RenderWindow& window)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			window.draw(level[i][j]);
		}
	}

	for (auto& coin : coins)
	{
		window.draw(coin.getCoin());
	}
}
