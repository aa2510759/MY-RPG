#ifndef RADIATIONGUY_H
#define RADIATIONGUY_H

#include "Enemy.h"

class RadiationGuy : public Enemy
{
public:
	RadiationGuy() {}
	RadiationGuy(std::string name, int strength, int health, int gold, int speed);

	virtual int attack() override;
private:
	int radiation = 30;
	std::string nameOfAtk = "Radiation";  // special attack
};

#endif