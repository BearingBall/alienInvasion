#include "textureCollector.h"

std::shared_ptr<sf::Texture> TextureCollector::operator[](const std::string index)
{
	const bool flag = collector.find(index) == collector.end();
	std::shared_ptr<sf::Texture>& texture = collector[index];
	if (flag)
	{
		texture.reset(new sf::Texture);
		texture->loadFromFile(index);
	}
	return texture;
}
