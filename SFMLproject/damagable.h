#pragma once

class Damagable
{

private:
	size_t maxHealth;
	size_t health = maxHealth;
	
public:
	Damagable(size_t _maxHealth = 100):maxHealth(_maxHealth) {}
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

	float percentageHealth() const
	{
		return static_cast<float>(health) / maxHealth;
	}
	
	bool alive() const
	{
		return health != 0;
	}
};