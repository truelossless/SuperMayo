#include "fileManager.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

std::map<std::string, sf::Texture> FileManager::m_textures;

sf::Texture* FileManager::getTexture(std::string path) {

	std::map<std::string, sf::Texture>::iterator i = m_textures.find(path);
	if (i != m_textures.end()) {
		// the texture is already loaded
		return &i->second;
	}

	// the texture isn't loaded
	m_textures[path].loadFromFile(path);
	return &m_textures[path];
}