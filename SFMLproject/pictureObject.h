#pragma once
#include <SFML/Graphics.hpp>

#include "object.h"
#include "textureCollector.h"

struct PictureObject final: Object
{
private:
	std::string textureName;
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;
public:
	PictureObject(const std::string& name):textureName(name),texture((*TextureCollector::instance())[name])
	{
		refreshSprite();
	}

	void refreshSprite();
	void refreshSprite(sf::IntRect rect);
	
	void setPosition(Vector2 point) override;
	void draw(sf::RenderWindow& window) override;
	
	bool ifOnMousePressed(Vector2 point) override;
	bool ifOnMouseOver(Vector2 point) const override;
	
	void ChangeColour(sf::Color color) override;
	
	const sf::Texture& getTexture() const;
	sf::Texture& getTexture();
	
	const sf::Sprite& getSprite() const;
	sf::Sprite& getSprite();
	
	const std::string& getTextureName() const;
	std::string& getTextureName();
};
