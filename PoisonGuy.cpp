#include "PoisonGuy.h"
using namespace std;



int rng5() // rng to randomly determine if the enemy gets a attack boost 
{
	std::srand(static_cast <unsigned int> (std::time(0)));
	int r = std::rand() % 5;
	return r;
}
PoisonGuy::PoisonGuy(string n, int s, int h, int g, int sp) : Enemy(n, s, h, g, sp){}

int PoisonGuy::attack()
{
	if (rng5() == 3)
	{
		return this->getStrength() + this->toxic;
	}
	return this->getStrength();
}