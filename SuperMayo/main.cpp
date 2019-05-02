#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <nlohmann/json.hpp>
#include <iostream>

#include "Game.h"
#include "Utils.h"
#include "Screen.h"

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	sf::RenderWindow window(sf::VideoMode(), "Super Mayo", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(60);

	Utils::setWindow(&window);

	Game* game = new Game(window);

	Screen::State state = Screen::State::GameRunning;

	while (window.isOpen()) {
		
		if (state == Screen::State::GameRunning) {
			state = game->update();
		}
		else if (state == Screen::State::GameOver) {
			delete game;
			game = new Game(window);
			state = Screen::State::GameRunning;
		}
		
		window.display();
	}

	return 0;
}