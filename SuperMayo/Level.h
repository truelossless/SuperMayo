#pragma once
#include <string>
#include <Box2D/Box2D.h>
#include <vector>

#include "Entity.h"

class Level {
public:
	Level(b2World* world);
	~Level();
	void load(std::string path);

private:
	b2World* m_world;
	std::vector<Entity*> m_grounds;
	std::vector<Entity*> m_platforms;
	std::vector<Entity*> m_monsters;
};

