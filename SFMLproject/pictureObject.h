#pragma once
#include <SFML/Graphics.hpp>

#include "object.h"

struct PictureObject final: Object
{
	std::string textureName;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	PictureObject(const std::string& name):textureName(name)
	{
		texture.loadFromFile(name);
		refreshSprite();
	}
	
	void refreshSprite()
	{
		sprite = sf::Sprite(texture);
	}

	void refreshSprite(sf::IntRect rect)
	{
		sprite = sf::Sprite(texture, rect);
	}

	void setPosition(Vector2 point) override
	{
		sprite.setPosition(point.x, point.y);
	}
	
	void draw(sf::RenderWindow &window) override
	{
		window.draw(sprite);
	}

	bool ifOnMousePressed(Vector2 point) override
	{
		return onMouseOver(point);
	}

	bool ifOnMouseOver(Vector2 point) const override
	{
		return (point.x > sprite.getPosition().x) && (point.x < (sprite.getPosition().x + sprite.getGlobalBounds().width)) &&
			(point.y > sprite.getPosition().y) && (point.y < (sprite.getPosition().y + sprite.getGlobalBounds().height));
	}

	void ChangeColour(sf::Color color) override
	{
		sprite.setColor(color);
	}

	const sf::Texture& getTexture() const
	{
		return texture;
	}

	sf::Texture& getTexture()
	{
		return texture;
	}

	const sf::Sprite& getSprite() const
	{
		return sprite;
	}

	sf::Sprite& getSprite()
	{
		return sprite;
	}
};
