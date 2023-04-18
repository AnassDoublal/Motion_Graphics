#include "Grid.h"

Grid::Grid(int t_id, sf::Vector2f t_pos) : m_id(t_id), m_pos(t_pos)
{

}

Grid::Grid(int t_id) : m_id(t_id)
{
}

void Grid::addNeighbour(int t_cellId)
{
	m_neighbours.push_back(t_cellId);
}

bool Grid::isMarked() const
{
	return m_marked;
}

void Grid::setMarked(bool t_val)
{
	m_marked = t_val;
}

std::vector<int>& Grid::neighbours()
{
	return m_neighbours;
}
