#include "ParticleSystem.h"

void ParticleSystem::init(sf::Vector2f t_pos, sf::Color color)
{
	position = t_pos;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i] = Particle(position, sf::Vector2f(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2), color);
	}
}

void ParticleSystem::update()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].update();
	}
}

void ParticleSystem::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].render(t_window);
	}
}
