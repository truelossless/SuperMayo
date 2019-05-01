#include "Game.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include "Utils.h"

Game::Game(sf::RenderWindow & window):
	m_window(window),
	m_player(0, 100, &m_world),
	m_world(b2Vec2(0.f, 9.8f)),
	m_level(&m_world) {

	m_world.SetContactListener(&m_contactListener);
	m_view = window.getDefaultView();
	m_view.setCenter(m_player.getBody()->GetPosition().x * Entity::SCALE, m_view.getCenter().y);

	m_level.load("levels/level1.json");
}

Screen::State Game::update() {
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
	}

	// handle inputs
	b2Vec2 force(0, 0);
	float impulse = 0;

	if (sf::Joystick::isConnected(0)) {

		float xJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float yJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

		if (xJoy < -15 || xJoy > 15) force.x = xJoy;
		if (sf::Joystick::isButtonPressed(0, 0)) impulse = -50;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) force.x = -100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) force.x = 100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) impulse = -50;

	m_player.getBody()->ApplyForceToCenter(force, true);
	m_player.jump(impulse); // will not trigger if the player is already jumping

	m_window.clear();

	// add one more frame to the simulation
	m_world.Step(1.f / 60.f, 8, 3);

	// scrolling
	b2Vec2 pos = Entity::SCALE * m_player.getBody()->GetPosition();
	sf::Vector2f viewPos = m_view.getCenter();

	//float step = player.getBody()->GetLinearVelocity().x * Entity::SCALE / 30.f;
	float step = (viewPos.x - pos.x) * Entity::SCALE / 400.f;
	viewPos.x -= step;

	m_view.setCenter(viewPos);
	m_window.setView(m_view);

	// update the physics for everything
	for (b2Body* body = m_world.GetBodyList(); body; body = body->GetNext()) {
		Entity *entity = static_cast<Entity*>(body->GetUserData());
		entity->update();
	}


	// draw everything
	for (b2Body* body = m_world.GetBodyList(); body; body = body->GetNext()) {
		Block *block = static_cast<Block*>(body->GetUserData());
		m_window.draw(block->getShape());
	}
	
	// the player is out of the screen
	if (m_player.getBody()->GetPosition().y * Entity::SCALE > Utils::getWindowSize().y * 2) {
		return State::GameOver;
	}
	else {
		return State::GameRunning;
	}

}
