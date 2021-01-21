#pragma once
struct VectorInt final
{
	size_t x;
	size_t y;

	bool operator==(const VectorInt& other) const
	{
		return (x == other.x) && (y == other.y);
	}
};