#include "Entity.h"

const float Entity::SCALE = 30.f;

Entity::Entity() {
}

b2Body* Entity::getBody() const {
	return m_body;
}