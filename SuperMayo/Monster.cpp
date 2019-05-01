#include "Monster.h"

#include <random>

#include "Entity.h"

Monster::Monster(float x, float y, b2World * world):
	Player(x, y, world) {

	// limit the speed of the monster
	m_maxVelocity = 200.f;

	// seed so all the monsters don't jump at the same time
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 10800);
	seed = sf::milliseconds(dist(mt));

	getBody()->SetLinearDamping(10);
	getBody()->SetGravityScale(15);
}

Entity::Type Monster::getEntityType() {
	return Entity::Type::Monster;
}

void Monster::update() {
	
	// should the monster jump ?
	if ((jumpClock.getElapsedTime() + seed).asSeconds() > 5) {
		jump(-120);
		jumpClock.restart();

		// remove the seed after the first use
		seed = sf::milliseconds(0);

	}
	else {
		getBody()->ApplyForceToCenter(b2Vec2(150, 0), true);
	}
	
	Block::update();
}

