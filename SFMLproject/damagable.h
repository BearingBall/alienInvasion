#pragma once

class Damagable
{
public:
	Damagable() = default;
	virtual ~Damagable() = default;

	void healthSet(size_t _health)
	{
		health = _health;
		maxHealth = _health;
	}

	void healing(size_t damage)
	{
		if (maxHealth - health > damage)
		{
			health += damage;
		}
		else
		{
			health = maxHealth;
		}
	}
	
	void givingDamage(size_t damage)
	{
		if (health > damage)
		{
			health -= damage;
		}
		else
		{
			health = 0;
		}
	}

	bool alive()
	{
		return health != 0;
	}
	
private:
	size_t health = 100;
	size_t maxHealth = 100;
};