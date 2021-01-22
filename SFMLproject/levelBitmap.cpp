#include "levelBitmap.h"

void Bitmap::calculateOtherPoint(VectorInt yourPoint, VectorInt otherPoint)
{
	if ((point(yourPoint.x, yourPoint.y) > point(otherPoint.x, otherPoint.y) + 1) &&
		(point(yourPoint.x, yourPoint.y) != x * y))
	{
		point(yourPoint.x, yourPoint.y) = point(otherPoint.x, otherPoint.y) + 1;
		diving(yourPoint);
	}
}

void Bitmap::diving(VectorInt current)
{
	calculateOtherPoint({current.x - 1, current.y}, {current.x, current.y});
	calculateOtherPoint({current.x + 1, current.y}, {current.x, current.y});
	calculateOtherPoint({current.x, current.y - 1}, {current.x, current.y});
	calculateOtherPoint({current.x, current.y + 1}, {current.x, current.y});
}

bool Bitmap::horizontalStepper(Enemy& enemy, Vector2& currentGlobal) const
{
	if ((enemy.getCoordinate() - currentGlobal).y < wallSize / 4)
	{
		enemy.stepDown(1);
		enemy.rotation(Vector2(0, 20));
		return true;
	}
	if ((enemy.getCoordinate() - currentGlobal).y > wallSize * 3 / 4)
	{
		enemy.stepUp(1);
		enemy.rotation(Vector2(0, -20));
		return true;
	}
	return false;
}

bool Bitmap::verticalStepper(Enemy& enemy, Vector2& currentGlobal) const
{
	if ((enemy.getCoordinate() - currentGlobal).x < wallSize / 4)
	{
		enemy.stepRigth(1);
		enemy.rotation(Vector2(20, 0));
		return true;
	}
	if ((enemy.getCoordinate() - currentGlobal).x > wallSize * 3 / 4)
	{
		enemy.stepLeft(1);
		enemy.rotation(Vector2(-20, 0));
		return true;
	}
	return false;
}

void Bitmap::load(Level& level)
{
	std::for_each(level.getWalls().begin(), level.getWalls().end(),
	              [this](Wall& wall)
	              {
		              if (wall.type == wallType::wall)
		              {
			              point(wall.getCoordinate().x / wallSize, wall.getCoordinate().y / wallSize) = x * y;
		              }
	              });
}

int& Bitmap::point(size_t indexX, size_t indexY)
{
	if (indexX >= x)
	{
		return map[x * y];
	}
	if (indexY >= y)
	{
		return map[x * y];
	}

	return map[indexX + indexY * x];
}

void Bitmap::debug()
{
	for (size_t y_ = 0; y_ < y; y_++)
	{
		for (size_t x_ = 0; x_ < x; x_++)
		{
			int a = point(x_, y_);
			if (a > 100)
			{
				std::cout << a << " ";
			}
			else if (a > 10)
			{
				std::cout << a << "  ";
			}
			else
			{
				std::cout << a << "   ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
}

void Bitmap::mapRefresh(Creature& player)
{
	VectorInt newStartPoint = {
		static_cast<size_t>(player.getCoordinate().x / wallSize),
		static_cast<size_t>(player.getCoordinate().y / wallSize)
	};
	if (!(startPoint == newStartPoint))
	{
		std::for_each(map.begin(), map.end(), [this](int& tmp)
		{
			if (tmp < x * y)
				tmp = x * y - 1;
		});
		startPoint = newStartPoint;
		point(startPoint.x, startPoint.y) = 0;
		diving(startPoint);
		//debug();
	}
}

void Bitmap::enemyMove(Enemy& enemy)
{
	VectorInt current = {
		static_cast<size_t>((enemy.getCoordinate().x + enemy.modelBound().x / 2) / wallSize),
		static_cast<size_t>((enemy.getCoordinate().y + enemy.modelBound().y / 2) / wallSize)
	};

	Vector2 currentGlobal(current.x, current.y);
	currentGlobal *= wallSize;

	if (point(current.x - 1, current.y) < point(current.x, current.y))
	{
		if (!horizontalStepper(enemy, currentGlobal))
		{
			enemy.stepLeft(1);
			enemy.rotation(Vector2(-20, 0));
		}
	}
	else if (point(current.x + 1, current.y) < point(current.x, current.y))
	{
		if (!horizontalStepper(enemy, currentGlobal))
		{
			enemy.stepRigth(1);
			enemy.rotation(Vector2(20, 0));
		}
	}
	else if (point(current.x, current.y - 1) < point(current.x, current.y))
	{
		if (!verticalStepper(enemy, currentGlobal))
		{
			enemy.stepUp(1);
			enemy.rotation(Vector2(0, -20));
		}
	}
	else if (point(current.x, current.y + 1) < point(current.x, current.y))
	{
		if (!verticalStepper(enemy, currentGlobal))
		{
			enemy.stepDown(1);
			enemy.rotation(Vector2(0, 20));
		}
	}
}
