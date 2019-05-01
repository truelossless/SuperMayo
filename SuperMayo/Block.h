#pragma once

#include "Entity.h"

class Block : public Entity {

public:
	Block(float x, float y, float w, float h, b2World* world, b2BodyType type);

	// inherited methods
	virtual void update();
	virtual Entity::Type getEntityType();
	virtual sf::Shape& getShape();
private:
	sf::RectangleShape m_shape;
};