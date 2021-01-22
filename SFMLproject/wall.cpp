#include "wall.h"

void Wall::draw(sf::RenderWindow& window, Vector2 shift, Vector2 levelSize, float scroll)
{
	model.refreshSprite(sf::IntRect(0, 0, model.getTexture().getSize().x, model.getTexture().getSize().y));
	model.setPosition((coordinate + shift) * scroll);
	model.getSprite().setScale(sf::Vector2f(size / model.getTexture().getSize().x * scroll,
	                                        size / model.getTexture().getSize().y * scroll));
	model.draw(window);
}

bool Wall::operator==(const Wall& other) const
{
	return coordinate == other.getCoordinate();
}
