#pragma once

#include "Block.h"

class Player : public Block {
public:
	Player(float x, float y, float w, float h, b2World* world);
	
	void jump(float impulse);
	bool getJump() const;
	void resetJump();
	void setFacingRight(bool facing);

	// inherited methods
	virtual Entity::Type getEntityType();
	virtual void update();

private:
	bool m_jumping = false;

protected:
	float m_maxVelocity = 400.f;
	bool m_facingRight = true;
	std::vector<sf::Texture*> m_textures;
};

