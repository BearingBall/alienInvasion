#pragma once
#include "gun.h"
#include "enemy.h"
#include "objectCollider.h"

class BulletEnemyHitter final 
{
public:
	static void operate(Gun& gun, std::vector<Enemy>& enemies)
	{
		std::for_each(gun.getBullets().begin(), gun.getBullets().end(), [&gun ,&enemies](Bullet& bullet)
		{
			std::for_each(enemies.begin(),enemies.end(),[&gun, &bullet](Enemy& enemy)
			{
				if (!bullet.getEndOfLife() && ObjectCollider::isCollides(bullet.getModel(),enemy.getModel()))
				{
					bullet.getEndOfLife() = true;
					enemy.givingDamage(gun.getDamage());
				}
			});
		});
	}
};