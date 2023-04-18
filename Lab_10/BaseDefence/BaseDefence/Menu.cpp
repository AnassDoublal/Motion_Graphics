#include "Menu.h"

Menu::Menu(sf::RenderWindow& t_window) : m_window(t_window)
{
}

// Run game
void Menu::run(sf::Time& timeSinceLastUpdate, sf::Clock& clock, sf::Time& timePerFrame, sf::RenderWindow& window, GAME_STATE& gameState, Game& game)
{
	processEvents(); // as many as possible
	timeSinceLastUpdate += clock.restart();
	while (timeSinceLastUpdate > timePerFrame)
	{
		timeSinceLastUpdate -= timePerFrame;
		processEvents(); // at least 60 fps
		update(window, gameState, game); //60 fps
	}
	render(m_window); // as many as possible
}

// Process events
void Menu::processEvents()
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
void Menu::processGameEvents(sf::Event& event)
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

void Menu::init() {
	font.loadFromFile("resources/fonts/rubik.ttf");

	titleText.setFont(font);
	titleText.setString("FIGHT OR DIE");
	titleText.setCharacterSize(60);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(510.0f, 100.0f);

	nameText.setFont(font);
	nameText.setString("Made by Adrian Sokolowski & Anass Doublal");
	nameText.setCharacterSize(25);
	nameText.setFillColor(sf::Color::White);
	nameText.setPosition(450.0f, 800.0f);

	play.setSize(sf::Vector2f(300.0f, 100.0f));
	play.setPosition(550.0f, 320.0f);

	playHovered.setSize(sf::Vector2f(300.0f, 100.0f));
	playHovered.setFillColor(sf::Color::Yellow);
	playHovered.setPosition(550.0f, 320.0f);

	playText.setFont(font);
	playText.setString("Play");
	playText.setCharacterSize(30);
	playText.setFillColor(sf::Color::Black);
	playText.setPosition(play.getPosition().x + play.getGlobalBounds().width / 2.0f - playText.getGlobalBounds().width / 2.0f, play.getPosition().y + play.getGlobalBounds().height / 2.0f - playText.getGlobalBounds().height / 2.0f);

	exit.setSize(sf::Vector2f(300.0f, 100.0f));
	exit.setPosition(550.0f, 550.0f);

	exitHovered.setSize(sf::Vector2f(300.0f, 100.0f));
	exitHovered.setFillColor(sf::Color::Yellow);
	exitHovered.setPosition(550.0f, 550.0f);
	exitText.setFont(font);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(30);
	exitText.setFillColor(sf::Color::Black);
	exitText.setPosition(exit.getPosition().x + exit.getGlobalBounds().width / 2.0f - exitText.getGlobalBounds().width / 2.0f, exit.getPosition().y + exit.getGlobalBounds().height / 2.0f - exitText.getGlobalBounds().height / 2.0f);
}

void Menu::update(sf::RenderWindow& window, GAME_STATE& gameState, Game& game) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (play.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		isHoveringPlay = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//isClickingPlay = true;
			gameState = GAME_STATE::GAME;
		}
	}
	else
		isHoveringPlay = false;

	if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		isHoveringExit = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//isClickingExit = true;
			window.close();
		}
	}
	else
		isHoveringExit = false;
}

void Menu::render(sf::RenderWindow& window) {
	window.draw(play);
	if (isHoveringPlay)
		window.draw(playHovered);
	window.draw(exit);
	if (isHoveringExit)
		window.draw(exitHovered);
	window.draw(titleText);
	window.draw(nameText);
	window.draw(playText);
	window.draw(exitText);
}