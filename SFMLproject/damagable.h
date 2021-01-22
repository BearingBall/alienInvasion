#pragma once

class Damagable
{
private:
	size_t maxHealth;
	size_t health = maxHealth;
	
public:
	Damagable(size_t _maxHealth = 100):maxHealth(_maxHealth) {}
	virtual ~Damagable() = default;

	void healthSet(size_t _health);
	void healing(size_t damage);
	void givingDamage(size_t damage);
	float percentageHealth() const;
	bool alive() const;
};