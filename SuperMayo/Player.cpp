#include "Player.h"

#include <iostream>
#include <Box2D/Box2D.h>

Player::Player(float x, float y, b2World* world): 
	Block(x, y, 30, 70, world, b2_dynamicBody) {

	getBody()->SetGravityScale(8);
	getBody()->SetFixedRotation(true);

	b2PolygonShape jumpSensorShape;
	jumpSensorShape.SetAsBox(12 / SCALE, 5 / SCALE, b2Vec2(0, 35 / SCALE), 0);

	b2FixtureDef jumpSensorFixtureDef;
	jumpSensorFixtureDef.shape = &jumpSensorShape;
	jumpSensorFixtureDef.isSensor = true;
	jumpSensorFixtureDef.userData = reinterpret_cast<int*>(FixtureType::JumpSensor);

	m_body->CreateFixture(&jumpSensorFixtureDef);
}

void Player::jump(float impulse) {

	if (!m_jumping && impulse != 0) {
		getBody()->ApplyLinearImpulseToCenter(b2Vec2(0, impulse), true);
		m_jumping = true;
	}
}

bool Player::getJump() const {
	return m_jumping;
}

void Player::resetJump() {
	m_jumping = false;
}

Entity::Type Player::getEntityType() {
	return Entity::Type::Player;
}

void Player::update() {
	
	// cap the speed to a maximum
	b2Vec2 linearVelocity = getBody()->GetLinearVelocity();

	if (linearVelocity.x > m_maxVelocity / SCALE) {
		linearVelocity.x = m_maxVelocity / SCALE;
	}
	else if (linearVelocity.x < -m_maxVelocity / SCALE) {
		linearVelocity.x = -m_maxVelocity / SCALE;
	}
	
	getBody()->SetLinearVelocity(linearVelocity);
	Block::update();
}