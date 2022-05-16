#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <ctime>
#include <random>
#include <cstdlib>

class Enemy
{
public:
	Enemy() {}
	Enemy(std::string n, int s, int h, int g, int sp)
	{
		setName(n);
		setStrength(s);
		setHealth(h);
		setSpeed(sp);
		setGold(g);
	}
	void setSpeed(int s) { speed = s; }
	int getSpeed() { return speed; }
	void setName(std::string n) { name = n; }
	std::string getName() { return name; }
	void setStrength(int s) { strength = s; }
	int getStrength() { return strength; }
	void setHealth(int h) { health = h; }
	int getHealth() { return health; }
	void setGold(int g) { gold = g; }
	int getGold() { return gold; }

	virtual int attack() = 0; // funtion can be variant depending on child class

private:
	int speed{};
	std::string name{};
	int strength{};
	int health{};
	int gold{};
};

#endif
