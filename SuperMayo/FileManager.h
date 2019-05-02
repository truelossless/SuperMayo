#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class FileManager
{
public:
	static sf::Texture* getTexture(std::string path);

private:
	static std::map<std::string, sf::Texture> m_textures;

};

