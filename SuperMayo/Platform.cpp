#include "Platform.h"

#include <iostream>

Platform::Platform(float x, float y, float w, float h, float l, std::string texture, b2Vec2 s, b2World * world) :
	Block(x, y, w, h, texture, world, b2_kinematicBody) {
	m_startPos = x + w / 2;
	m_speed = s;
	m_length = l;

	getBody()->SetLinearVelocity(1 / Entity::SCALE * m_speed);
}

void Platform::update() {

	if (getBody()->GetPosition().x * Entity::SCALE > m_startPos + m_length) {
		getBody()->SetLinearVelocity(-1 / Entity::SCALE * m_speed);
	}
	else if (getBody()->GetPosition().x * Entity::SCALE < m_startPos) {
		getBody()->SetLinearVelocity(1 / Entity::SCALE * m_speed);
	}

	Block::update();
}
