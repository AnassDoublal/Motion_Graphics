#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Marker.h"
class Pulse
{
public:
	Pulse();
	void update(double dt);
	void render(sf::RenderWindow& t_window);
	void init(const sf::Vector2f&);
	sf::CircleShape m_pulse;
	// vector of markers that gets incremented when collision between pulse and enemy happens
	std::vector<Marker> m_markers;
	bool showMarkers = true;
private:
	// if true radius is positivem if false it is negative
	bool m_increasePulse = true;
	// checks if radius should expand or contract
	void shouldPulseGrow();
	// gets the origin as the new origin with radius accounted for
	const sf::Vector2f getOriginPoint();
	// startubg radius
	double m_radius = 5;
	// speed at which radius increases or decreases
	double m_radiusTransformation = 10;
	double m_currentTime = 0;

};