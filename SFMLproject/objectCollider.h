#pragma once
#include "pictureObject.h"

class ObjectCollider final
{
private:
	static bool isPointInRect(const Vector2 point, const Vector2 rectCoord, const Vector2 rectBound)
	{
		if ((point.x > rectCoord.x && point.x < rectCoord.x + rectBound.x)&&
			(point.y > rectCoord.y && point.y < rectCoord.y + rectBound.y))
		{
			return true;
		}
		return false;
	}
public:
	static bool isCollides(const PictureObject& first, const PictureObject& second)
	{
		const Vector2 rectCoord = { second.getSprite().getGlobalBounds().left, second.getSprite().getGlobalBounds().top };
		const Vector2 rectBound = { second.getSprite().getGlobalBounds().width, second.getSprite().getGlobalBounds().height };
		
		if (isPointInRect({ first.getSprite().getGlobalBounds().left, first.getSprite().getGlobalBounds().top },
						rectCoord, rectBound))
		{
			std::cout << first.getSprite().getGlobalBounds().left << " " << first.getSprite().getGlobalBounds().top << "\n";
			return true;
		}
		if (isPointInRect({ first.getSprite().getGlobalBounds().left + first.getSprite().getGlobalBounds().width, 
			first.getSprite().getGlobalBounds().top },
			rectCoord, rectBound))
		{
			return true;
		}
		if (isPointInRect({ first.getSprite().getGlobalBounds().left, 
			first.getSprite().getGlobalBounds().top + first.getSprite().getGlobalBounds().height },
			rectCoord, rectBound))
		{
			return true;
		}
		if (isPointInRect({ first.getSprite().getGlobalBounds().left + first.getSprite().getGlobalBounds().width, 
			first.getSprite().getGlobalBounds().top + first.getSprite().getGlobalBounds().height },
			rectCoord, rectBound))
		{
			return true;
		}
		return false;
	}
};