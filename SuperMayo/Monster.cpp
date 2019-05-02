#include "Monster.h"

#include <random>
#include <iostream>

#include "Entity.h"
#include "FileManager.h"

Monster::Monster(float x, float y, b2World * world):
	Player(x, y, 32, 32, world) {

	// limit the speed of the monster
	m_maxVelocity = 200.f;

	// seed so all the monsters don't jump at the same time
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 10800);
	m_seed = sf::milliseconds(dist(mt));

	getBody()->SetLinearDamping(10);
	getBody()->SetGravityScale(15);

	m_textures.push_back(FileManager::getTexture("assets/tiles/kraax1.png"));
	m_textures.push_back(FileManager::getTexture("assets/tiles/kraax2.png"));
	m_textures.push_back(FileManager::getTexture("assets/tiles/kraax3.png"));
	m_frames = 3;

	// sensor to define when the monster should change its walking direction
	b2PolygonShape rightSensorShape;
	rightSensorShape.SetAsBox(3 / SCALE, 5 / SCALE, b2Vec2(16 / SCALE, 0), 0);

	b2PolygonShape leftSensorShape;
	leftSensorShape.SetAsBox(3 / SCALE, 5 / SCALE, b2Vec2(-16 / SCALE, 0), 0);

	b2FixtureDef sensorFixtureDef;
	sensorFixtureDef.shape = &rightSensorShape;
	sensorFixtureDef.isSensor = true;
	sensorFixtureDef.userData = reinterpret_cast<int*>(FixtureType::RightSensor);

	m_body->CreateFixture(&sensorFixtureDef);

	sensorFixtureDef.shape = &leftSensorShape;
	sensorFixtureDef.userData = reinterpret_cast<int*>(FixtureType::LeftSensor);

	m_body->CreateFixture(&sensorFixtureDef);
}

Entity::Type Monster::getEntityType() {
	return Entity::Type::Monster;
}

void Monster::update() {
	
	// should we update the sprite ?
	int time = m_spriteClock.getElapsedTime().asMilliseconds() / 200;
	
	if (time == m_frames) {
		m_spriteClock.restart();
	} else if (time != m_currentFrame) {
		m_currentFrame = time;
		m_sprite.setTexture(*m_textures[m_currentFrame]);
	}

	// should the monster jump ?
	if ((m_jumpClock.getElapsedTime() + m_seed).asSeconds() > 5) {
		jump(-60);
		m_jumpClock.restart();

		// remove the seed after the first use
		m_seed = sf::milliseconds(0);
	}
	else {
		getBody()->ApplyForceToCenter(b2Vec2(m_force, 0), true);
	}
	
	Player::update();
}

void Monster::setFacingRight(bool facing) {
	m_facingRight = facing;
	facing ? m_force = 100 : m_force = -100;
}

