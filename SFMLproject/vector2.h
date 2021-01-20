#pragma once


class Vector2 final
{
private:
	float maxSpeed = 200;
public:
	Vector2(float _x, float _y) : x(_x), y(_y)
	{
		
	}

	Vector2 operator*(float b) const
	{
		return { x*b,y*b };
	}

	Vector2 operator/(float b) const
	{
		return { x/b,y/b };
	}
	
	Vector2 operator+(const Vector2& b) const
	{
		return { x+b.x,y+b.y };
	}

	Vector2 operator+(const float& b) const
	{
		return { x + b,y + b };
	}
	
	Vector2 operator-(const Vector2& b) const
	{
		return { x - b.x,y - b.y };
	}
	
	Vector2& operator+=(const Vector2& b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}

	Vector2& operator*=(float b)
	{
		x *= b;
		y *= b;
		return *this;
	}

	bool operator==(const Vector2& b) const
	{
		return (x==b.x)&&(y==b.y);
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2& exping(float b, float c)
	{
		if (x > 0)
		{
			x = (exp((x - b) / c) + b);
		}
		else
		{
			x = -1 * (exp((-1 * x - b) / c) + b);
		}
		if (y > 0)
		{
			y = (exp((y - b) / c) + b);
		}
		else
		{
			y = -1 * (exp((-1*y - b) / c) + b);
		}
		if (x > maxSpeed)
		{
			x = maxSpeed;
		}
		if (y > maxSpeed)
		{
			y = maxSpeed;
		}
		if (x < -maxSpeed)
		{
			x = -maxSpeed;
		}
		if (y < -maxSpeed)
		{
			y = -maxSpeed;
		}
		
		return *this;
	}

	float min()
	{
		return std::min(x, y);
	}
	
	float x;
	float y;
};