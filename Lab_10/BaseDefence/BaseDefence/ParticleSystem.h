#pragma once
#include "Particle.h"

int const MAX_PARTICLES = 5;
class ParticleSystem
{
public:
	ParticleSystem() = default;
	/// <summary>
	/// amount of particles on screen
	/// </summary>
	Particle particles[MAX_PARTICLES];
	// starting position of the particle
	void init(sf::Vector2f t_pos, sf::Color color);
	// particle movement
	void update();
	void render(sf::RenderWindow& t_window);

private:
	// position of the particle
	sf::Vector2f position;
};
