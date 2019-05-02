#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Monster : public Player {
public:
	Monster(float x, float y, b2World* world);
	
	// inherited methods
	virtual Entity::Type getEntityType();
	virtual void update();
	void setFacingRight(bool facing);

private:
	int m_frames;
	int m_currentFrame;
	float m_force = 100.f;

	sf::Clock m_jumpClock;
	sf::Clock m_spriteClock;
	sf::Time m_seed;
};

