#include "ContactListener.h"

#include "Entity.h"
#include "Player.h"

#include <iostream>

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	beginContactCallback(contact->GetFixtureA());
	beginContactCallback(contact->GetFixtureB());

}

void ContactListener::EndContact(b2Contact* contact) {

}

void ContactListener::beginContactCallback(b2Fixture* fixture) {
	// first collision object
	Entity* entity = static_cast<Entity*>(fixture->GetBody()->GetUserData());

	// get the fixture type
	Entity::FixtureType type = static_cast<Entity::FixtureType>(reinterpret_cast<int>(fixture->GetUserData()));

	if (type == Entity::FixtureType::JumpSensor) {
		Player* player = static_cast<Player*>(fixture->GetBody()->GetUserData());
		player->resetJump();
	}
}
