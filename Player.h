#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Weapon.h"

struct AmmoReserve
{
	int shotgunAmmo;
	int arrows;
	int pistolAmmo;
	int flares;
};
class Player
{
private:
	int health;
	int food;
	std::string name;
	std::vector <Weapon> inventory;
	Weapon currentW;
	int attack;
	int defense;
	int speed;
	int gold;
	int dificulty;
	Weapon currentW2;
	AmmoReserve ammoExcess;
	int currentIndex;

public:
	Player()
	{
		health = 100;
		name = "Lone Wanderer";
		food = 10;
		currentW = Weapon("name", -1, -1, -1);
		currentW2 = Weapon("name", -1, -1, -1);
		attack = 0;
		defense = 0;
		speed = 0;
		dificulty = 1;
		gold = 20;
		ammoExcess.arrows = 0;
		ammoExcess.flares = 0;
		ammoExcess.pistolAmmo = 0;
		ammoExcess.shotgunAmmo = 0;
	}
	Player(int h, std::string n, int f, int a, int d, int s, int di, int g)
	{
		setHealth(h);
		setName(n);
		setFood(f);
		setAttack(a);
		setDefense(d);
		setSpeed(s);
		setDificulty(di);
		setGold(g);
	}
	void setAmmoExcess(AmmoReserve a) { this->ammoExcess = a; }
	AmmoReserve getAmmoExcess() { return this->ammoExcess; }
	void setGold(int g) { this->gold = g; }
	int getGold() { return this->gold; }
	void setAttack(int a)
	{
		this->attack = a;
	}
	void setDificulty(int di)
	{
		this->dificulty = di;
	}
	void setDefense(int d)
	{
		this->defense = d;
	}
	void setSpeed(int s)
	{
		this->speed = s;
	}
	void setCurrentW(Weapon w)
	{
		this->currentW = w;
	}
	int getDificulty()
	{
		return this->dificulty;
	}
	Weapon getCurrentW()
	{
		return currentW;
	}
	void setHealth(int h)
	{
		if (h > 200)
		{
			h = 200;
			this->health = h;
		}
		else
		{
			this->health = h;
		}
	}
	void setFood(int f)
	{
		this->food = f;
	}
	void setName(std::string n)
	{
		this->name = n;
	}
	void setInvetory(Weapon w)
	{
		this->inventory.push_back(w);
	}
	Weapon getInventory(int i)
	{
		return this->inventory.at(i);
	}
	std::vector <Weapon> getAllWeapons()
	{
		return this->inventory;
	}
	int getFood()
	{
		return this->food;
	}
	int getAttack()
	{
		return this->attack;
	}
	int getDefense()
	{
		return this->defense;
	}
	int getSpeed()
	{
		return this->speed;
	}
	int getHealth()
	{
		return health;
	}
	std::string getName()
	{
		return name;
	}
	void setAtFunction(int i, Weapon w)
	{
		inventory.at(i) = w;
	}
	std::vector <Weapon> getAddressOfVector()
	{
		return this->inventory;
	}
	void setCurrentIndex(int i) { this->currentIndex = i; }
	int getCurrentIndex() { return this->currentIndex; }
	void checkStats()
	{
		std::cout << "\nName: " << getName() << std::endl
			<< "Food: " << getFood() << std::endl
			<< "Health: " << getHealth() << "/200" << std::endl;
		if (getCurrentW().getAmmo() == -1)
		{
			std::cout << "Weapon Equipped: none\n";
		}
		else
		{
			std::cout << "Weapon Equpped: " << getCurrentW().getName() << std::endl;

		}


		std::cout << "Attack: " << getAttack() << std::endl
			<< "Defense: " << getDefense() << std::endl
			<< "Speed: " << getSpeed() << std::endl
			<< "Gold: " << getGold() << std::endl;


	}
	void checkInventory()
	{
		std::cout << "Inventory:\n";
		for (unsigned int i = 0; i < inventory.size(); i++)
		{
			std::cout << i + 1 << ") " << inventory.at(i).getName() << std::endl;
		}
	}
	void getWeaponAmmo()
	{

		if (getCurrentW().getAmmo() == -1)
		{
			std::cout << "\nWeapon Equipped: none\n";
		}
		else
		{
			std::cout << "\nWeapon Equpped: " << getCurrentW().getName() << std::endl;

		}


		if (currentW.getName().compare("Shotgun") == 0)
		{
			std::cout << "Ammo: " << currentW.getAmmo() << std::endl;

		}
		else if (currentW.getName().compare("Pistol") == 0)
		{
			std::cout << "Ammo: " << currentW.getAmmo() << std::endl;
		}
		else if (currentW.getName().compare("Flare gun") == 0)
		{
			std::cout << "Flares: " << currentW.getAmmo() << std::endl;
		}
		else if (currentW.getName().compare("Bow") == 0)
		{
			std::cout << "Arrows: " << currentW.getAmmo() << std::endl << std::endl;
		}


		checkInventory();

		std::cout << std::endl << std::endl;
		std::cout << "Extra ammo:\n"
			<< "Flares: " << getAmmoExcess().flares << std::endl
			<< "Shotgun ammo: " << getAmmoExcess().shotgunAmmo << std::endl
			<< "Pistol ammo: " << getAmmoExcess().pistolAmmo << std::endl
			<< "Arrows: " << getAmmoExcess().arrows << std::endl;
	}
};

#endif