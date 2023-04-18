#pragma once

#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "GameState.h"

class Menu {
public:
	Menu(sf::RenderWindow&);
	void run(sf::Time&, sf::Clock&, sf::Time&, sf::RenderWindow&, GAME_STATE&, Game&);
	void processEvents();
	void processGameEvents(sf::Event&);
	void init();
	void update(sf::RenderWindow&, GAME_STATE&, Game&);
	void render(sf::RenderWindow&);
private:
	sf::Font font;

	sf::Text titleText;
	sf::Text nameText;

	sf::RectangleShape play;
	sf::RectangleShape playHovered;
	sf::Text playText;

	sf::RectangleShape exit;
	sf::RectangleShape exitHovered;
	sf::Text exitText;

	bool isHoveringPlay = false;
	bool isClickingPlay = false;

	bool isHoveringExit = false;
	bool isClickingExit = false;

	sf::RenderWindow& m_window;
};