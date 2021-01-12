#pragma once
#include <map>
#include <SFML/Graphics.hpp>


class TextureCollector final
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> collector;
	TextureCollector() = default;
	~TextureCollector() = default;
public:
	static TextureCollector* instance()
	{
		static TextureCollector inst;
		return &inst;
	}
	
	std::shared_ptr<sf::Texture> operator[](const std::string index)
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
};
