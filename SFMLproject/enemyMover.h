#pragma once
#include "enemy.h"
#include "LevelBitmap.h"

class EnemyMover final
{
private:
	static void stupidMovement(Enemy& enemy, Creature& player)
	{
		if (enemy.getCoordinate().y < player.getCoordinate().y)
		{
			enemy.stepDown(1);
		}
		if (enemy.getCoordinate().y > player.getCoordinate().y)
		{
			enemy.stepUp(1);
		}
		if (enemy.getCoordinate().x < player.getCoordinate().x)
		{
			enemy.stepRigth(1);
		}
		if (enemy.getCoordinate().x > player.getCoordinate().x)
		{
			enemy.stepLeft(1);
		}
	}

public:
	static void move(std::vector<Enemy>& enemies, Creature& player, Level& level, Bitmap& bitmap)
	{
		if (!enemies.empty())
		{
			std::for_each(enemies.begin(), enemies.end(),
				[&player, &level, &bitmap](Enemy& enemy)
			{
				enemy.hit(player);
					
				if ((enemy.getCoordinate() - player.getCoordinate()).length() < player.modelBound().min())
				{
					enemy.rotation(player.getCoordinate() - enemy.getCoordinate());
					enemy.animationStatic();
				}
				else
					if ((enemy.getCoordinate() - player.getCoordinate()).length() < level.getWallSize())
					{
						stupidMovement(enemy, player);
						enemy.rotation(player.getCoordinate() - enemy.getCoordinate());
						enemy.animationMoving();
					}
					else
					{
						bitmap.enemyMove(enemy);
						enemy.animationMoving();
					}
			});
		}
	}
};
