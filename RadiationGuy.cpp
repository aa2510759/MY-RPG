#include "RadiationGuy.h"

using namespace std;

int rng10() // rng to randomly determine if the enemy gets a attack boost 
{
	std::srand(static_cast <unsigned int> (std::time(0)));
	int r = std::rand() % 10;
	return r;
}

RadiationGuy::RadiationGuy(string n, int s, int h, int g, int sp) : Enemy(n, s, h, g, sp){}

int RadiationGuy::attack()
{
	if (rng10() == 3)
	{
		return this->getStrength() + this->radiation;
	}
	return this->getStrength();
}