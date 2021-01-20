#pragma once
#include "animator.h"
#include "creature.h"
#include "movable.h"
#include "damagable.h"
#include "timer.h"


class Enemy final: public Creature
{
private:
	size_t damage = 10;
	Timer timerAnimation;
	Animator animator;

	Timer timerHitting;
	float hitRange = 60;
public:
	Enemy(Vector2 coord, size_t maxHealth):Creature(ResourceFileNaming::alian0Name, coord,  maxHealth), timerAnimation(0.2), animator(ResourceFileNaming::alian0Name), timerHitting(3)
	{
		animator.addState(ResourceFileNaming::alian1Name);
		animator.addState(ResourceFileNaming::alian2Name);
		animator.addState(ResourceFileNaming::alian1Name);
	}
	~Enemy() = default;

	void animationMoving()
	{
		if (timerAnimation.isTimerOut())
		{
			animator.setNext(getModel());
		}
	}

	void animationStatic()
	{
		if (timerAnimation.isTimerOut())
		{
			animator.setDefault(getModel());
		}
	}

	void hit(Creature& player)
	{
		if (((coordinate-player.getCoordinate()).length() <= hitRange) && (timerHitting.isTimerOut()))
		{
			player.givingDamage(damage);
		}
	}
};
