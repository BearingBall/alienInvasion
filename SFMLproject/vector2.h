#pragma once


class Vector2 final
{
public:
	Vector2(float _x, float _y) : x(_x), y(_y)
	{
		
	}

	Vector2 operator*(float b) const
	{
		return { x*b,y*b };
	}

	Vector2 operator+(const Vector2& b) const
	{
		return { x+b.x,y+b.y };
	}

	Vector2& operator+=(const Vector2& b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}

	bool operator==(const Vector2& b) const
	{
		return (x==b.x)&&(y==b.y);
	}
	
	float x;
	float y;
};