#include "vector2.h"

#include <algorithm>

Vector2 Vector2::operator*(float b) const
{
	return {x * b, y * b};
}

Vector2 Vector2::operator/(float b) const
{
	return {x / b, y / b};
}

Vector2 Vector2::operator+(const Vector2& b) const
{
	return {x + b.x, y + b.y};
}

Vector2 Vector2::operator+(const float& b) const
{
	return {x + b, y + b};
}

Vector2 Vector2::operator-(const Vector2& b) const
{
	return {x - b.x, y - b.y};
}

Vector2& Vector2::operator+=(const Vector2& b)
{
	x += b.x;
	y += b.y;
	return *this;
}

Vector2& Vector2::operator*=(float b)
{
	x *= b;
	y *= b;
	return *this;
}

bool Vector2::operator==(const Vector2& b) const
{
	return (x == b.x) && (y == b.y);
}

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::min() const
{
	return std::min(x, y);
}

Vector2 Vector2::moduleNormingImage()
{
	return Vector2(x > 0 ? 1 : -1, y > 0 ? 1 : -1);
}
