#pragma once
#include "pictureObject.h"

class ObjectCollider final
{
private:
	static bool isPointInRect(const Vector2 point, const Vector2 rectCoord, const Vector2 rectBound);
public:
	static bool isCollides(const PictureObject& first, const PictureObject& second);
};