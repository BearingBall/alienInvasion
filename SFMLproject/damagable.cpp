#include "damagable.h"

void Damagable::healthSet(size_t _health)
{
	health = _health;
	maxHealth = _health;
}

void Damagable::healing(size_t damage)
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

void Damagable::givingDamage(size_t damage)
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

float Damagable::percentageHealth() const
{
	return static_cast<float>(health) / maxHealth;
}

bool Damagable::alive() const
{
	return health != 0;
}
