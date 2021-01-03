#pragma once
#include <SFML/Graphics.hpp>

#include "object.h"

struct PictureObject final: Object
{
public:
	PictureObject(std::string &name)
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

	bool ifOnMouseOver(Vector2 point) override
	{
		return (point.x > sprite.getPosition().x) && (point.x < (sprite.getPosition().x + sprite.getTextureRect().width)) &&
			(point.y > sprite.getPosition().y) && (point.y < (sprite.getPosition().y + sprite.getTextureRect().height));
	}

	void ChangeColour(sf::Color color) override
	{
		sprite.setColor(color);
	}
	
	sf::Texture texture;
	sf::Sprite sprite;
};
