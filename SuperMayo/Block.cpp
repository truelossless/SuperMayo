#include "Block.h"
#include <iostream>

Block::Block(float x, float y, float w, float h, b2World* world, b2BodyType type) {

	//convert the lower-left coordinates to the center-based coordinates of Box2D
	x = x + w / 2;
	y = y + h / 2;

	// SFML
	m_shape.setSize(sf::Vector2f(w, h));
	m_shape.setOrigin(w / 2, h / 2);
	m_shape.setPosition(x, y);

	// Box2D
	m_world = world;


	b2BodyDef bodyDef;
	bodyDef.position.Set(x / SCALE, y / SCALE);
	bodyDef.type = type;

	// keep a reference to this object inside the Box2D body
	bodyDef.userData = this;

	b2PolygonShape b2shape;
	b2shape.SetAsBox(w / 2 / SCALE, h / 2 / SCALE);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.shape = &b2shape;
	fixtureDef.userData = reinterpret_cast<int*>(FixtureType::Collision);

	m_body = m_world->CreateBody(&bodyDef);
	m_body->CreateFixture(&fixtureDef);
}

void Block::update() {
	m_shape.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	m_shape.setRotation(m_body->GetAngle() * 180 / b2_pi);
}

sf::Shape& Block::getShape() {
	return m_shape;
}

Entity::Type Block::getEntityType() {
	return Entity::Type::Block;
}
