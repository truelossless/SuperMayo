#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Utils {
public:
	Utils();
	static void setWindow(sf::RenderWindow* window);
	static sf::Vector2u getWindowSize();

private:
	static sf::RenderWindow* m_window;
};

