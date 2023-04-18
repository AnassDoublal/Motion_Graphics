#include "Collision.h"

bool Collisions::collision(sf::Sprite& t_obj1, sf::Sprite& t_obj2)
{
	// gets the bounding box of both objects
	CollisionObject objBox1(t_obj1);
	CollisionObject objBox2(t_obj2);

	// sets the points onto an axis
	sf::Vector2f axes[4] =
	{
		sf::Vector2f
		(objBox1.Points[1].x - objBox1.Points[0].x,
		objBox1.Points[1].y - objBox1.Points[0].y),

		sf::Vector2f
		(objBox1.Points[1].x - objBox1.Points[2].x,
		objBox1.Points[1].y - objBox1.Points[2].y),

		sf::Vector2f
		(objBox2.Points[0].x - objBox2.Points[3].x,
		objBox2.Points[0].y - objBox2.Points[3].y),

		sf::Vector2f
		(objBox2.Points[0].x - objBox2.Points[1].x,
		objBox2.Points[0].y - objBox2.Points[1].y)
	};
	// checks each axis for collisions
	for (int i = 0; i < 4; i++) // For each axis...
	{
		float minObjBox1, maxObjBox1, minObjBox2, maxoObjBox2;

		// ... project the points of both bounding boxes onto the axis ...
		objBox1.ProjectOntoAxis(axes[i], minObjBox1, maxObjBox1);
		objBox2.ProjectOntoAxis(axes[i], minObjBox2, maxoObjBox2);

		// if they dont overlap there is no collsion
		if (!((minObjBox2 <= maxObjBox1) && (maxoObjBox2 >= minObjBox1)))
			return false;
	}
	return true;
}

bool Collisions::collision(sf::CircleShape& t_obj1, sf::Sprite& t_obj2)
{
	CollisionObject objBox1(t_obj1);
	CollisionObject objBox2(t_obj2);

	// sets the points onto an axis
	sf::Vector2f axes[4] =
	{
		sf::Vector2f
		(objBox1.Points[1].x - objBox1.Points[0].x,
		objBox1.Points[1].y - objBox1.Points[0].y),

		sf::Vector2f
		(objBox1.Points[1].x - objBox1.Points[2].x,
		objBox1.Points[1].y - objBox1.Points[2].y),

		sf::Vector2f
		(objBox2.Points[0].x - objBox2.Points[3].x,
		objBox2.Points[0].y - objBox2.Points[3].y),

		sf::Vector2f
		(objBox2.Points[0].x - objBox2.Points[1].x,
		objBox2.Points[0].y - objBox2.Points[1].y)
	};
	// checks each axis for collisions
	for (int i = 0; i < 4; i++) // For each axis...
	{
		float minObjBox1, maxObjBox1, minObjBox2, maxoObjBox2;

		// ... project the points of both bounding boxes onto the axis ...
		objBox1.ProjectOntoAxis(axes[i], minObjBox1, maxObjBox1);
		objBox2.ProjectOntoAxis(axes[i], minObjBox2, maxoObjBox2);

		// if they dont overlap there is no collsion
		if (!((minObjBox2 <= maxObjBox1) && (maxoObjBox2 >= minObjBox1)))
			return false;
	}
	return true;
}
