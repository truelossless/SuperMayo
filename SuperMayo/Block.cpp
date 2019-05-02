#include "Block.h"

#include <iostream>

#include "FileManager.h"

Block::Block(float x, float y, float w, float h, std::string texture, b2World* world, b2BodyType type):
	m_texture(FileManager::getTexture(texture)) {

	//convert the lower-left coordinates to the center-based coordinates of Box2D
	x = x + w / 2;
	y = y + h / 2;

	// SFML
	m_texture->setRepeated(true);
	m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h)));
	m_sprite.setOrigin(w / 2, h / 2);
	m_sprite.setPosition(x, y);

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
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	m_sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);
}

sf::Sprite& Block::getSprite() {
	return m_sprite;
}

Entity::Type Block::getEntityType() {
	return Entity::Type::Block;
}
