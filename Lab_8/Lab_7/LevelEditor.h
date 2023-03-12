#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"

class LevelEditor
{
public:
	void init(sf::Font&, sf::RenderWindow&, sf::View&);
	void update(sf::RenderWindow&);
	void controlView(sf::View&);
	std::vector<std::vector<int>> generateLevel(sf::RenderWindow&);
	void render(sf::RenderWindow&);
private:
	sf::RectangleShape platformTile;
	sf::RectangleShape obstacleTile;
	sf::RectangleShape jumpPadTile;
	sf::RectangleShape gravitySwitchTile;
	sf::RectangleShape finishLineTile;

	sf::Text platformText;
	sf::Text obstacleText;
	sf::Text jumpPadText;
	sf::Text gravitySwitchText;
	sf::Text finishLineText;

	std::vector<sf::RectangleShape> grid;
	float gridRectX = .0f;
	float gridRectY = .0f;

	sf::RectangleShape activeTile;
	std::vector<sf::RectangleShape> drawnTiles;
	bool isTileOccupied = false;

	float viewSpeed = 30.0f;
	int viewCoolDown = 0;

	float initialViewX = .0f;

	bool isEraseTileSelected = false;

	int levelData[55][20];
};