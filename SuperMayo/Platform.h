#pragma once

#include "Block.h"

class Platform :
	public Block
{
public:
	Platform(float x, float y, float w, float h, float l, std::string texture, b2Vec2 s, b2World* world);
	
	// inherited methods
	void update();

private:
	float m_startPos;
	float m_length;
	b2Vec2 m_speed;
};

