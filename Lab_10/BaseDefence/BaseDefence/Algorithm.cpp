#include "Algorithm.h"

std::vector<sf::Vector2f>  Algorithm::breadthFirst(std::vector<Grid>& t_grid, int t_startCellId, int t_destCellId)
{
	std::vector<sf::Vector2f>gridPositions;
	// if false run algo until goal is reached
	bool goalReached = false;
	// current cell starting as the start cell
	int currentCell = t_startCellId;
	// set the starting cell as marked
	t_grid[t_startCellId].setMarked(true);
	// push the starting cell to the queue
	queue.push(t_startCellId);
	/// <summary>
	/// while queue is not empty and goal hasnt been reach continue algorithm
	/// </summary>
	/// <param name="t_grid"> the grid being tested</param>
	/// <param name="t_startCellId"> the start point of the cell</param>
	/// <param name="t_destCellId"> the destination of the cell</param>
	while (!queue.empty() && goalReached == false)
	{
		// move the current cell to the front of the queue
		currentCell = queue.front();
		
		for (auto adjacent : t_grid[currentCell].neighbours())
		{
			// if not marked, set as marked and make the current cell the previous cell id for the current grid id
			if (!t_grid[adjacent].isMarked())
			{
				t_grid[adjacent].setMarked(true);
				t_grid[adjacent].m_previousCellId = currentCell;
				// push adjacent to the queue
				queue.push(adjacent);
			}
			// if the id of the adjacent tile is the id of the destination, we reached out goal
			if (t_grid[adjacent].m_id == t_destCellId)
			{
				// set goal as true for it to be reached
				goalReached = true;
				// set the current cell as the previous cell Id of the destination cell
				currentCell = t_grid[adjacent].m_previousCellId;
				break;
			}
		}
		queue.pop();
			
	}
	// if goal is reached trace back the fastest route to the starting pos
	while(goalReached == true)
	{
		currentCell = t_grid[currentCell].m_previousCellId;

		//std::cout << currentCell << std::endl;
		if (currentCell != t_startCellId)
		{
			gridPositions.push_back(t_grid[currentCell].m_pos);
		}
		
		// leave if starting location has been reached
		if (currentCell == t_startCellId)
		{
			return gridPositions;
		}
	}
	return std::vector<sf::Vector2f>();
}

void Algorithm::neighbours(std::vector<Grid>& t_grid)
{
	for (size_t i = 0; i < t_grid.size(); i++)
	{
		for (size_t direction = 0; direction < 9; direction++) {
			if (direction == 4) continue; // Skip 4, this is ourself.

			// index = rowNumber * numCols + colNumber

			int row = t_grid[i].m_id / NUM_COLS;
			int col = t_grid[i].m_id % NUM_COLS;
			int n_row = row + ((direction % 3) - 1); // Neighbor row
			int n_col = col + ((direction / 3) - 1); // Neighbor column

			// Check the bounds:
			if (n_row >= 0 && n_row < NUM_ROWS && n_col >= 0 && n_col < NUM_COLS) {

				// A valid neighbor:
				//std::cout << "Neighbor: " << n_col << " : " << n_row << ": " << t_grid[i].m_id << std::endl;
				int index = n_row * NUM_COLS + n_col;
				t_grid[i].addNeighbour(index);
			}
		}

	}
}

void Algorithm::init()
{
	/// <summary>
	/// position of each id on the screen
	/// </summary>
	for (size_t i = 0; i < NUM_ROWS; i++)
	{
		for (size_t j = 0; j < NUM_COLS; j++)
		{
			m_gridPos[i][j].y = i * gridSizeX;
			m_gridPos[i][j].x = j * gridSizeY;
		}
	}
	/// <summary>
	/// initialize the grid array with the id and position of the grid
	/// </summary>
	int index = 0;
	for (size_t i = 0; i < NUM_ROWS; i++)
	{
		for (size_t j = 0; j < NUM_COLS; j++)
		{
			grid.push_back(Grid(index, m_gridPos[i][j]));
			index += 1;
		}
	}
	// add the neighbours for each grid tile
	neighbours(grid);
	// breadthFirst implemention 
	//breadthFirst(grid, 23, 1687);
	int o = 0;
}

int Algorithm::getObjId(sf::Vector2f t_pos)
{
	int indexX = t_pos.x / gridSizeX;
	int indexY = t_pos.y / gridSizeY;

	int index = (indexY * NUM_COLS) + indexX;

	return index;
}

