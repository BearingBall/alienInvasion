#pragma once


class Vector2 final
{
public:
	Vector2(float _x, float _y) : x(_x), y(_y)
	{
		
	}

	Vector2 operator*(float b) const;
	Vector2 operator/(float b) const;
	Vector2 operator+(const Vector2& b) const;
	Vector2 operator+(const float& b) const;
	Vector2 operator-(const Vector2& b) const;
	Vector2& operator+=(const Vector2& b);
	Vector2& operator*=(float b);
	bool operator==(const Vector2& b) const;
	float length() const;
	float min() const;
	Vector2 moduleNormingImage();

	float x;
	float y;
};