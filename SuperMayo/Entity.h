#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Entity {

public:
	enum class Type {
		Monster,
		Player,
		Block,
		Wall,
	};

	enum class FixtureType {
		Collision,
		JumpSensor
	};

	static const float SCALE; // = 30.f

	Entity();

	b2Body* getBody() const;

	virtual void update() = 0;
	virtual Type getEntityType() = 0;

protected:
	b2Body* m_body;
	b2World* m_world;
};

