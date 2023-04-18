#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"thor-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib")
#pragma comment(lib,"thor.lib")
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
#pragma comment(lib,"libyaml-cppmdd") 

#include "Game.h"
#include "Menu.h"

/// <summary>
/// Game by Adrian Sokolowski and Anass Doublal
/// </summary>
/// <returns></returns>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1440, 900, 32), "GAME");

	Menu menu(window);
	Game game(window);

	GAME_STATE gameState = GAME_STATE::MENU;

	menu.init();
	game.init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	double const FPS = 60.0;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps

	while (window.isOpen())
	{
		window.clear();

		switch (gameState)
		{
		case GAME_STATE::MENU:
			menu.run(timeSinceLastUpdate, clock, timePerFrame, window, gameState, game);
			break;

		case GAME_STATE::GAME:
			game.run(timeSinceLastUpdate, clock, timePerFrame);
			break;
		}

		window.display();
	}

}