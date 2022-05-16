#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <ctime>
#include <random>
#include <cstdlib>

class Weapon
{
private:
	std::string name;
	int damage;
	int price;

public:
	int ammo;

	Weapon()
	{
		name = "Weapon";
		damage = 0;
		ammo = -1;
	}

	Weapon(std::string n, int d, int p, int a)
	{
		setName(n);
		setDamage(d);
		setPrice(p);
		setAmmo(a);
	}

	void setName(std::string n) { this->name = n; }
	std::string getName() { return this->name; }

	void setDamage(int d) { this->damage = d; }
	int getDamage() { return this->damage; }

	void setAmmo(int a) { this->ammo = a; }
	int getAmmo() { return this->ammo; }


	void setPrice(int p) { this->price = p; }
	int getPrice() { return this->price; }
};
#endif



