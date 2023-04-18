#pragma once
#include "iostream"
#include <vector>
#include "SFML/Graphics.hpp"

int const NUM_ROWS = 180;
int const NUM_COLS = 288;

class Grid
{
public:
	Grid() = default;
	/// <summary>
	/// Construct grid
	/// </summary>
	Grid(int t_id, sf::Vector2f m_pos);
	Grid(int t_id);

	void addNeighbour(int t_cellId); // To add a neighbour
	bool isMarked() const; // returns the member variable m_marked;

	void setMarked(bool t_val); // setter method to set the value of member m_marked
	std::vector<int>& neighbours(); // To return the list of neighbours

	int m_id; // the id of the grid
	int m_previousCellId;

	sf::Vector2f m_pos; // position of the grid 
private:
	bool m_marked{ false }; // This is used by the Breadth-First Search algorithm.
	std::vector<int> m_neighbours; // A one dimensional array containing all the neighbour
};

