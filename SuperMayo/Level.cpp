#include "Level.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Block.h"
#include "Utils.h"
#include "Platform.h"
#include "Monster.h"

Level::Level(b2World* world) {
	m_world = world;
}

Level::~Level()
{

	for (int i = 0; i < m_grounds.size(); i++) {
		delete m_grounds[i];
	}

	for (int i = 0; i < m_platforms.size(); i++) {
		delete m_platforms[i];
	}

	for (int i = 0; i < m_monsters.size(); i++) {
		delete m_monsters[i];
	}

}

void Level::load(std::string path) {
	
	std::ifstream file(path);
	nlohmann::json json;
	file >> json;

	// create the ground
	for (int i = 0; i < json["ground"].size(); i++) {

		nlohmann::json ground = json["ground"][i];
		float x = ground["from"].get<float>();
		float w = ground["to"].get<float>() - ground["from"].get<float>();
		float h = ground["height"].get<float>();
		float y = Utils::getWindowSize().y - h;
		std::string texture = ground["tex"].get<std::string>();
		texture = "assets/tiles/" + texture + ".png";

		m_grounds.push_back(new Block(x, y, w, h, texture, m_world, b2_staticBody));
	}

	// create the platforms
	for (int i = 0; i < json["platforms"].size(); i++) {

		nlohmann::json platform = json["platforms"][i];
		float x = platform["x"].get<float>();
		float w = platform["width"].get<float>();
		float h = platform["height"].get<float>();
		float y = platform["y"].get<float>();
		y = Utils::getWindowSize().y - y;
		float l = platform["length"].get<float>();
		l = l - w;
		float sx = platform["speed"]["x"].get<float>();
		float sy = platform["speed"]["y"].get<float>();
		std::string texture = platform["tex"].get<std::string>();
		texture = "assets/tiles/" + texture + ".png";

		if (l == 0.f) {
			m_platforms.push_back(new Block(x, y, w, h, texture ,m_world, b2_staticBody));
		}
		else {
			m_platforms.push_back(new Platform(x, y, w, h, l, texture, b2Vec2(sx, sy), m_world));
		}

	}

	// create the monsters
	for (int i = 0; i < json["monsters"].size(); i++) {
		nlohmann::json monster = json["monsters"][i];
		float x = monster["x"].get<float>();
		float y = monster["y"].get<float>();
		y = Utils::getWindowSize().y - y;

		m_monsters.push_back(new Monster(x, y, m_world));
	}
}
