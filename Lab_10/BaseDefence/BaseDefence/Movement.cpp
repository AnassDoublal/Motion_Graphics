#include "Movement.h"

sf::Vector2f Movement::recoilControl(sf::Vector2f t_pos, int t_faceDir)
{
	switch (t_faceDir)
	{
	case 1:
		t_pos.y += recoil;
		std::cout << t_faceDir << std::endl;
		break;
	case 2:
		t_pos.x -= recoil;
		std::cout << t_faceDir << std::endl;
		break;
	case 3:
		t_pos.y -= recoil;
		std::cout << t_faceDir << std::endl;
		break;
	case 4:
		t_pos.x += recoil;
		std::cout << t_faceDir << std::endl;
		break;
	default:
		break;
	}
	std::cout << t_pos.x << std::endl;
	return t_pos;
}
