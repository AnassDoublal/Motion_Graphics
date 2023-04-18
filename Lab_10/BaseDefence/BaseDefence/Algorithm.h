#pragma once
#include "Grid.h"
#include <queue>
class Algorithm
{
public:
	Algorithm() = default;
	std::vector<sf::Vector2f> breadthFirst(std::vector<Grid>& t_grid, int t_startCellId, int t_destCellId);
	void neighbours(std::vector<Grid>& t_grid); // adding neigbours to each id 
	void init();
	int  getObjId(sf::Vector2f);
	std::vector<Grid> grid; 
private:
	std::queue<int> queue;
	
	float gridSizeX = 5.0f;
	float gridSizeY = 5.0f;
	sf::Vector2f m_gridPos[NUM_ROWS][NUM_COLS]; // positions of the ids on the map
};