#pragma once
#include "bullet.h"
#include "creature.h"
#include "bulletDrawer.h"

class Gun final
{
private:
	Creature& gunOwner;
	std::vector<Bullet> bullets;
	Timer shootCoolDown;
	float scatter = 10;
	float damage = 3;
public:
	Gun(Creature& _gunOwner): gunOwner(_gunOwner), shootCoolDown(0.4)
	{
		
	}

	void render(sf::RenderWindow& window, Level& level, Camera& camera)
	{
		bullets.erase(std::remove_if(bullets.begin(),bullets.end(),[](Bullet& bullet)
		{
			return bullet.getEndOfLife();
		}), bullets.end());
		
		std::for_each(bullets.begin(), bullets.end(), [&level, &window, &camera, this](Bullet& bullet)
		{
			BulletDrawer::draw(window, bullet, camera);
			bullet.render(window, level);
		});
	}
	
	void shoot()
	{
		if (shootCoolDown.isTimerOut())
		{
			bullets.emplace_back(gunOwner, gunOwner.getRotation());
			bullets.emplace_back(gunOwner, gunOwner.getRotation() + scatter);
			bullets.emplace_back(gunOwner, gunOwner.getRotation() - scatter);
		}
	}

	float getDamage()
	{
		return damage;
	}
	
	std::vector<Bullet>& getBullets()
	{
		return bullets;
	}
};
