
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
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>
#include "Level.h"
#include "Collision.h"

sf::Texture coinTexture;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 756), "Using sf::View"); // Create window

	window.setFramerateLimit(60); // Set a framrate limit to reduce the CPU load

	sf::Texture texMap; // Create the world texture and sprite
	texMap.loadFromFile("world.png");
	sf::Sprite map(texMap);

	sf::Texture texLink; // Create the link texture and sprite 
	sf::Texture texLink1; // Create the link texture and sprite 
	texLink.loadFromFile("bon.png");
	texLink1.loadFromFile("yon.png");
	sf::RectangleShape bulletPlayer1;
	bulletPlayer1.setSize(sf::Vector2f(10, 10));
	bulletPlayer1.setPosition(-10000, -10000);
	sf::RectangleShape bulletPlayer2;
	bulletPlayer2.setSize(sf::Vector2f(10, 10));
	bulletPlayer2.setPosition(-10000, -10000);
	sf::Sprite player2(texLink);
	player2.setScale(2, 2);
	player2.setOrigin(player2.getGlobalBounds().width / 2.0f, player2.getGlobalBounds().height / 2.0f);
	player2.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	sf::Sprite player1(texLink1);
	player1.setScale(2, 2);
	player1.setOrigin(player1.getGlobalBounds().width / 2.0f, player1.getGlobalBounds().height / 2.0f);
	player1.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	sf::View fixed = window.getView(); // The 'fixed' view will never change

	sf::View standard = fixed; // The 'standard' view will be the one that gets always displayed

	unsigned int size = 200; // The 'minimap' view will show a smaller picture of the map
	sf::View minimap(sf::FloatRect(standard.getCenter().x, standard.getCenter().y, static_cast<float>(size), static_cast<float>(window.getSize().y * size / window.getSize().x)));
	minimap.setViewport(sf::FloatRect(1.f - static_cast<float>(minimap.getSize().x) / window.getSize().x - 0.02f, 1.f - static_cast<float>(minimap.getSize().y) / window.getSize().y - 0.02f, static_cast<float>(minimap.getSize().x) / window.getSize().x, static_cast<float>(minimap.getSize().y) / window.getSize().y));
	minimap.zoom(4.f);

	// The 'left' and the 'right' view will be used for splitscreen displays
	sf::View left(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y)));
	left.setViewport(sf::FloatRect(0.f, 0.f, 0.5, 1.f));
	sf::View right(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y)));
	right.setViewport(sf::FloatRect(0.5, 0.f, 0.5, 1.f));

	sf::RectangleShape miniback; // We want to draw a rectangle behind the minimap
	miniback.setPosition(minimap.getViewport().left * window.getSize().x - 5, minimap.getViewport().top * window.getSize().y - 5);
	miniback.setSize(sf::Vector2f(minimap.getViewport().width * window.getSize().x + 10, minimap.getViewport().height * window.getSize().y + 10));
	miniback.setFillColor(sf::Color(160, 8, 8));

	Level level;
	level.init();

	Collision collision;

	//for (size_t i = 0; i < 50; i++)
	//{
	//	for (size_t j = 0; j < 50; j++)
	//	{
	//		if (collision.playerToWall(player1, level.level) || collision.playerToWall(player2, level.level))
	//		{
	//			level.level[i][j].setFillColor(sf::Color::Magenta);
	//		}
	//	}
	//}

	sf::Font font;
	sf::Text player1CoinsText;
	sf::Text player2CoinsText;
	int player1Coins = 0;
	int player2Coins = 0;

	font.loadFromFile("arial.ttf");
	player1CoinsText.setFont(font);
	player1CoinsText.setFillColor(sf::Color::Yellow);
	player1CoinsText.setOutlineThickness(2);
	player1CoinsText.setOutlineColor(sf::Color::Black);
	player1CoinsText.setCharacterSize(30);
	player1CoinsText.setPosition(100.0f, 50.0f);
	player1CoinsText.setString("Coins collected : 0");

	player2CoinsText.setFont(font);
	player2CoinsText.setFillColor(sf::Color::Yellow);
	player2CoinsText.setOutlineThickness(2);
	player2CoinsText.setOutlineColor(sf::Color::Black);
	player2CoinsText.setCharacterSize(30);
	player2CoinsText.setPosition(650.0f, 50.0f);
	player2CoinsText.setString("Coins collected : 0");

	bool gameOver = false;

	sf::Text gameOverText;

	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setCharacterSize(50);
	gameOverText.setPosition(350.0f, 350.0f);

	left.setCenter(player1.getPosition());
	right.setCenter(player2.getPosition());
	while (window.isOpen()) // As long as the window is open
	{
		sf::Event event; // Normal event handling

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
			{
				standard.zoom(1.f + event.mouseWheel.delta * 0.1f);
				left.zoom(1.f + event.mouseWheel.delta * 0.1f);
				right.zoom(1.f + event.mouseWheel.delta * 0.1f);

			}

		}

		level.update();

		for (size_t i = 0; i < sizeof(level.coins) / sizeof(Coin); i++)
		{
			if (collision.playerToCoin(player1, level.coins[i]))
			{
				player1Coins++;
				player1CoinsText.setString("Coins collected : " + std::to_string(player1Coins));
				level.coins[i].getCoin().setScale(.0f, .0f);
			}

			if (collision.playerToCoin(player2, level.coins[i]))
			{
				player2Coins++;
				player2CoinsText.setString("Coins collected : " + std::to_string(player2Coins));
				level.coins[i].getCoin().setScale(.0f, .0f);
			}

		}

		if (player1Coins + player2Coins == sizeof(level.coins) / sizeof(Coin))
		{
			gameOver = true;
			
			if (player1Coins > player2Coins)
				gameOverText.setString("Yellow wins!");
			else if (player1Coins < player2Coins)
				gameOverText.setString("Blue wins!");
			else if (player1Coins == player2Coins)
				gameOverText.setString("Players tie!");
		}

		std::cout << static_cast<int>(collision.playerToWall(player1, level.level)) << "\n";

		switch (collision.playerToWall(player1, level.level))
		{
			case Direction::LEFT:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					// Move left
					player1.move(-4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player1.move(0.f, -4.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player1.move(0.f, 4.f);
				}
				break;
			case Direction::RIGHT:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player1.move(4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player1.move(0.f, -4.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player1.move(0.f, 4.f);
				}
				break;
			case Direction::UP:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					// Move left
					player1.move(-4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player1.move(4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player1.move(0.f, -4.f);
				}
				break;
			case Direction::DOWN:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					// Move left
					player1.move(-4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player1.move(4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player1.move(0.f, 4.f);
				}
				break;
			case Direction::NONE:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					// Move left
					player1.move(-4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player1.move(4.f, 0.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player1.move(0.f, -4.f);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player1.move(0.f, 4.f);
				}

		}

		switch (collision.playerToWall(player2, level.level))
		{
		case Direction::LEFT:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Move left
				player2.move(-4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player2.move(0.f, -4.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player2.move(0.f, 4.f);
			}
			break;
		case Direction::RIGHT:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player2.move(4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player2.move(0.f, -4.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player2.move(0.f, 4.f);
			}
			break;
		case Direction::UP:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Move left
				player2.move(-4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player2.move(4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player2.move(0.f, -4.f);
			}
			break;
		case Direction::DOWN:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Move left
				player2.move(-4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player2.move(4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player2.move(0.f, 4.f);
			}
			break;
		case Direction::NONE:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Move left
				player2.move(-4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player2.move(4.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player2.move(0.f, -4.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player2.move(0.f, 4.f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			bulletPlayer1.setPosition(player1.getPosition());

		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
		{
			bulletPlayer2.setPosition(player2.getPosition());
		}
		if (bulletPlayer1.getPosition().x != -10000)
		{
			bulletPlayer1.move(0, -1);
		}
		if (bulletPlayer2.getPosition().x != -10000)
		{
			bulletPlayer2.move(0, -1);
		}
		right.setCenter(player2.getPosition());
		left.setCenter(player1.getPosition());
		minimap.setCenter(sf::Vector2f(player2.getPosition().x + (player1.getPosition().x) / 2, player2.getPosition().y + (player1.getPosition().y) / 2));
		window.clear(); // Remove old content

		if (!gameOver)
		{
			window.setView(left);
			level.render(window);
			//window.draw(map);
			window.draw(player1);
			window.draw(bulletPlayer1);
			window.draw(bulletPlayer2);
			window.draw(player2);
			window.setView(right);
			level.render(window);
			//window.draw(map);
			window.draw(bulletPlayer1);

			window.draw(bulletPlayer2);
			window.draw(player1);
			window.draw(player2);

			window.setView(fixed); // Draw 'GUI' elements with fixed positions

			//window.draw(miniback);

			window.draw(player1CoinsText);
			window.draw(player2CoinsText);

			//window.setView(minimap); // Draw minimap
			//level.render(window);
			//window.draw(map);
		}
		else
		{
			window.setView(fixed);
			window.draw(gameOverText);
		}

		window.display(); // Show everything
	}

	return 0;
}