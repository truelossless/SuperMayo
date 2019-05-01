#include "Utils.h"

sf::RenderWindow* Utils::m_window = nullptr;

Utils::Utils() {
}

void Utils::setWindow(sf::RenderWindow* window)
{
	m_window = window;
}

sf::Vector2u Utils::getWindowSize() {
	return m_window->getSize();
}
