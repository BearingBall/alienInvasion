#include "camera.h"
#include <cmath>
#include "vector2.h"

Vector2 Camera::exping(Vector2 velocity) const
{
	if (velocity.x > 0)
	{
		velocity.x = (exp((velocity.x - expingArea) / expingStrongParam) + expingArea);
	}
	else
	{
		velocity.x = -1 * (exp((-1 * velocity.x - expingArea) / expingStrongParam) + expingArea);
	}
	if (velocity.y > 0)
	{
		velocity.y = (exp((velocity.y - expingArea) / expingStrongParam) + expingArea);
	}
	else
	{
		velocity.y = -1 * (exp((-1 * velocity.y - expingArea) / expingStrongParam) + expingArea);
	}
	velocity.x = std::clamp(velocity.x, -maxSpeed, maxSpeed);
	velocity.y = std::clamp(velocity.y, -maxSpeed, maxSpeed);
	return velocity;
}

void Camera::cameraMover(sf::RenderWindow& window, Vector2& playerCoordinate)
{
	if ((getCoordinate() - (playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling())).length() > expingArea)
	{
		getCoordinate() +=
			exping(playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling() - getCoordinate())*speed;
	}
	else
	{
		getCoordinate() += (playerCoordinate - Vector2(window.getSize().x, window.getSize().y) / 2 / getScrollScaling() - getCoordinate())*speed;
	}
}
