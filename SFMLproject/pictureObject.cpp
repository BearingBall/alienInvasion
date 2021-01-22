#include "pictureObject.h"

void PictureObject::refreshSprite()
{
	sprite = sf::Sprite(*texture);
}

void PictureObject::refreshSprite(sf::IntRect rect)
{
	sprite = sf::Sprite(*texture, rect);
}

void PictureObject::setPosition(Vector2 point)
{
	sprite.setPosition(point.x, point.y);
}

void PictureObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool PictureObject::ifOnMousePressed(Vector2 point)
{
	return onMouseOver(point);
}

bool PictureObject::ifOnMouseOver(Vector2 point) const
{
	return (point.x > sprite.getPosition().x) && (point.x < (sprite.getPosition().x + sprite.getGlobalBounds().width))
		&&
		(point.y > sprite.getPosition().y) && (point.y < (sprite.getPosition().y + sprite.getGlobalBounds().height));
}

void PictureObject::ChangeColour(sf::Color color)
{
	sprite.setColor(color);
}

const sf::Texture& PictureObject::getTexture() const
{
	return *texture;
}

sf::Texture& PictureObject::getTexture()
{
	return *texture;
}

const sf::Sprite& PictureObject::getSprite() const
{
	return sprite;
}

sf::Sprite& PictureObject::getSprite()
{
	return sprite;
}

const std::string& PictureObject::getTextureName() const
{
	return textureName;
}

std::string& PictureObject::getTextureName()
{
	return textureName;
}
