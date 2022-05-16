#ifndef POISONGUY_H
#define POISONGUY_H

#include "Enemy.h"

class PoisonGuy : public Enemy
{
public:
	PoisonGuy() {}
	PoisonGuy(std::string name, int strength, int health, int gold, int speed);
	virtual int attack() override;
private:
	int toxic = 25;
	std::string nameOfAtk = "Toxic"; // special attack
};

#endif
