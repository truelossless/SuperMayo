#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Monster : public Player {
public:
	Monster(float x, float y, b2World* world);
	
	// inherited methods
	virtual Entity::Type getEntityType();
	virtual void update();

private:
	int m_frames;
	sf::Clock jumpClock;
	sf::Time seed;
};

