#pragma once

#include "Entity.h"

class Block : public Entity {

public:
	Block(float x, float y, float w, float h, std::string texture, b2World *world, b2BodyType type);

	// inherited methods
	virtual void update();
	virtual Entity::Type getEntityType();
	virtual sf::Sprite& getSprite();

private:
	sf::Texture* m_texture;

protected:
	sf::Sprite m_sprite;
};