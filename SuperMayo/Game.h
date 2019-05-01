#pragma once

#include <SFML/Graphics.hpp>

#include "ContactListener.h"
#include "Player.h"
#include "Level.h"
#include "Screen.h"

class Game : public Screen
{
public:
	Game(sf::RenderWindow& window);
	
	// inherited methods
	State update();

private:
	sf::RenderWindow& m_window;
	sf::View m_view;
	b2World m_world;

	Level m_level;
	Player m_player;
	ContactListener m_contactListener;
};

