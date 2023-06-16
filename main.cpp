#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include <ctime>
#include <random>
#include <cstdlib>
#define NOMINMAX
#include <Windows.h>
#include "Enemy.h"
#include "PoisonGuy.h"
#include "RadiationGuy.h"
#include "Weapon.h"

using namespace std;

void clr()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
} // clears screen using native OS API

void characterSelect()
{
	std::cout << "Choose character:\n\n";
	std::cout << "1) Mercenary\n"
		<< "- 50 extra gold, 20 extra attack, start of with a shotgun\n\n"
		<< "2) Hunter\n"
		<< "- 15 extra Speed, start of with a bow and sword, start with 30 extra food\n\n"
		<< "3) Defender\n"
		<< "- 10 extra defense, start of with a pistol and bat, 30 extra health\n";
}
void c() // clears screen
{
	std::cout << "Press enter to continue...\n";
	std::cin.get();
	clr();

}
int grng(int p)
{
	std::srand(static_cast <unsigned int> (std::time(0)));
	int r = std::rand() % p;
	return r;
}
void actionList()
{
	std::cout << "1) Wander\n"
		<< "2) Equip weapon\n"
		<< "3) Look at stats\n"
		<< "4) Investigate nearby\n"
		<< "5) Forage for food\n"
		<< "6) Look at Weapons and ammmo\n"
		<< "7) Exit game\n"
		<< "Choose an action...\n\n";
}
void over() // not sure why this was made
{
	std::cout << "You're dead.\n";
}
Enemy* enemySpawn() // spawns new enemy
{
	int coin = 2;
	int enemyType = 0;
	enemyType = grng(coin) + 1;

	if (enemyType == 2)
	{
		std::cout << "Poison Guy" << " appears!\n";
		return new PoisonGuy("Poison Guy", 20, 50, 5, 5); // 25 toxic

	}
	else
	{
		std::cout << "Radiation Guy" << " appears!\n";
		return new RadiationGuy("Radiation Guy", 25, 60, 5, 10); // 30 radiation

	}
}
Enemy* enemySpawn2() //spawns harder enemy
{
	std::cout << "Super Radiation Guy" << " appears!\n";
	return new RadiationGuy(" Super Radiation Guy", 40, 70, 20, 20); //30
}
Enemy* enemySpawn3() // same
{
	std::cout << "Super Poion Guy" << " appears!\n";
	return new PoisonGuy(" Super Poison Guy", 30, 60, 20, 15); //25
}
void food(Player & myp)
{
	std::cout << "Found some food!\n"
		<< "(Health increased by 5)\n"
		<< "Food level increased\n";
	c();
	myp.setFood(myp.getFood() + 20);
	myp.setHealth(myp.getHealth() + 5); // increases health and food
}
int inputValidation(int x, std::string prompt)
{
	while (1)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			cout << "You have entered the wrong input\n\n";
			c();

			cout << prompt;
			std::cin >> x;

		}
		if (!std::cin.fail())
		{
			break;
		}
	}
	return x;
}
Player setStats(std::vector<Weapon> baseWeapons)
{
	Player myp2;
	int pointsEasy = 20;

	int easypts = 20; // JUST A REFERENCE variable
	int pointsMed = 15;
	int pointsHrd = 10;

	std::string difficultyPrompt = "Choose difficulty: \n1) Easy \n2) Normal \n3) Hard \n";
	int difChoice = -1;


	do
	{
		cout << difficultyPrompt;
		std::cin >> difChoice;
		c();
		difChoice = inputValidation(difChoice, difficultyPrompt);

		if (difChoice < 0 || difChoice > 3)
		{
			system("cls");
			std::cout << "Error Input.\n";
			c();
			std::cout << difficultyPrompt;
			std::cin >> difChoice;
			c();
		}


	} while (difChoice < 0 || difChoice > 3);


	myp2.setDificulty(difChoice);

	if (difChoice == 2)
	{
		pointsEasy = pointsMed;
	}
	else if (difChoice == 3)
	{
		pointsEasy = pointsHrd;
	}

	int charChoice = 0;

	do
	{
		characterSelect();
		std::cin >> charChoice;

	
		while (1)
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You have entered the wrong input\n\n";
				c();

				characterSelect();
				cin >> charChoice;

			}
			if (!cin.fail())
			{
				break;
			}
		}
		//********************character selectVVVVVVVVVVV

		if (charChoice == 1) //Mercenary
		{
			std::cin.ignore();
			myp2.setGold(myp2.getGold() + 50);
			myp2.setAttack(myp2.getAttack() + 20);
			myp2.setInvetory(baseWeapons.at(0));
			cout << "Shotgun obtained!\n";
			c();
		}
		else if
			(charChoice == 2) //Hunter
		{
			std::cin.ignore();
			myp2.setFood(myp2.getFood() + 30);
			myp2.setSpeed(myp2.getSpeed() + 15);
			myp2.setInvetory(baseWeapons.at(3));
			cout << "Sword obtained!\n";
			myp2.setInvetory(baseWeapons.at(5));
			cout << "Bow obtained!\n";
			c();
		}
		else if (charChoice == 3) //Police Officer
		{
			std::cin.ignore();
			myp2.setHealth(myp2.getHealth() + 30);
			myp2.setDefense(myp2.getDefense() + 10);
			myp2.setInvetory(baseWeapons.at(1));
			cout << "Pistol obtained!\n";
			myp2.setInvetory(baseWeapons.at(2));
			cout << "bat obtained!\n";
			c();
		}
		else
		{ 
			std::cin.ignore();
			std::cout << "Error input.\n";
			c();
		}
		//*************************************************
	} while (charChoice < 1 || charChoice > 3);

	while (pointsEasy > 0)

	{
		int input;
		int inputPointsH;
		int inputPointsA;

		std::cout << "Health: " << myp2.getHealth() << "\nAttack: " << myp2.getAttack()
			<< "\nDefense: " << myp2.getDefense() << "\nSpeed: " << myp2.getSpeed() << std::endl;
		std::cout << "You have " << pointsEasy << " left. \n";
		std::cout << "choose what stat you want to give points to.\n";
		std::cout << "1) Health\n";
		std::cout << "2) Attack\n";
		std::cout << "3) Defense\n";
		std::cout << "4) Speed\n";

		std::cin >> input;

		while (1)
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "You have entered the wrong input\n\n";
				c();
				std::cout << "Health: " << myp2.getHealth() << "\nAttack: " << myp2.getAttack()
					<< "\nDefense: " << myp2.getDefense() << "\nSpeed: " << myp2.getSpeed() << std::endl;
				std::cout << "You have " << pointsEasy << " left. \n";
				std::cout << "choose what stat you want to give points to.\n";
				std::cout << "1) Health\n";
				std::cout << "2) Attack\n";
				std::cout << "3) Defense\n";
				std::cout << "4) Speed\n";

				std::cin >> input;

			}
			if (!std::cin.fail())
			{
				break;
			}
		}

		if (input == 1)
		{

			std::cout << "You chose health.\n";
			c();

			std::cout << "How many points towards health?\n";
			std::cout << "You have " << pointsEasy << " left. \n";

			std::cin >> inputPointsH;
			std::cin.ignore();


			while (1)
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("cls");
					cout << "You have entered the wrong input\n\n";
					c();
					std::cout << "How many points towards health?\n";
					std::cout << "You have " << pointsEasy << " left. \n";


					std::cin >> inputPointsH;

				}
				if (!std::cin.fail())
				{
					break;
				}
			}

			if (inputPointsH  < 0 || inputPointsH > pointsEasy)
			{
				std::cout << "Error input.\n";
				c();
			}
			else if (((inputPointsH * 5) + myp2.getHealth()) > 200)
			{
				std::cout << "Error, goes past max stat.\n";
				c();
			}
			while (inputPointsH > pointsEasy || ((inputPointsH * 5) + myp2.getHealth()) > 200)
			{
				std::cout << "How many points towards health?\n";
				std::cout << "You have " << pointsEasy << " left. \n";

				std::cin >> inputPointsH;
				std::cin.ignore();


				while (1)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("cls");
						cout << "You have entered the wrong input\n\n";
						c();
						std::cout << "How many points towards health?\n";
						std::cout << "You have " << pointsEasy << " left. \n";


						std::cin >> inputPointsH;

					}
					if (!std::cin.fail())
					{
						break;
					}
				}


				if (inputPointsH  < 0 || inputPointsH > pointsEasy)
				{
					std::cout << "Error input.\n";
					c();
				}
				else if (((inputPointsH * 5) + myp2.getHealth()) > 200)
				{
					std::cout << "Error, goes past max stat.\n";
					c();
				}
			}

			pointsEasy -= inputPointsH;
			myp2.setHealth(myp2.getHealth() + (inputPointsH * 5));
			c();
		}

		else if (input == 2)
		{
			std::cout << "You chose attack.\n";
			c();

			std::cout << "How many points  towards attack?\n";
			std::cout << "You have " << pointsEasy << " left. \n";

			std::cin >> inputPointsA;
			std::cin.ignore();


			while (1)
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("cls");
					cout << "You have entered the wrong input\n\n";
					c();
					std::cout << "How many points towards attack?\n";
					std::cout << "You have " << inputPointsA << " left. \n";


					std::cin >> inputPointsH;

				}
				if (!std::cin.fail())
				{
					break;
				}
			}



			if (inputPointsA  < 0 || inputPointsA > pointsEasy)
			{
				std::cout << "Error input.\n";
				c();
			}
			else if (((inputPointsA)+myp2.getAttack()) > 20)
			{
				std::cout << "Error, goes past max stat.\n";
				c();
			}
			while (inputPointsA > pointsEasy || (((inputPointsA)+myp2.getAttack()) > 20))
			{
				std::cout << "How many points  towards Attack?\n";
				std::cout << "You have " << pointsEasy << " left. \n";

				std::cin >> inputPointsA;
				std::cin.ignore();



				while (1)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("cls");
						cout << "You have entered the wrong input\n\n";
						c();
						std::cout << "How many points towards attack?\n";
						std::cout << "You have " << inputPointsA << " left. \n";


						std::cin >> inputPointsH;

					}
					if (!std::cin.fail())
					{
						break;
					}
				}



				if (inputPointsA  < 0 || inputPointsA > pointsEasy)
				{
					std::cout << "Error input.\n";
					c();
				}
				else if (((inputPointsA)+myp2.getAttack()) > 20)
				{
					std::cout << "Error, goes past max stat.\n";
					c();
				}

			}

			myp2.setAttack(myp2.getAttack() + inputPointsA);
			pointsEasy -= inputPointsA;
			c();
		}


		else if (input == 3)
		{
			std::cout << "You chose Defense.\n";
			c();

			std::cout << "How many points  towards defense?\n";
			std::cout << "You have " << pointsEasy << " left. \n";

			std::cin >> inputPointsH;
			std::cin.ignore();


			while (1)
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("cls");
					cout << "You have entered the wrong input\n\n";
					c();
					std::cout << "How many points towards Defense?\n";
					std::cout << "You have " << inputPointsH << " left. \n";


					std::cin >> inputPointsH;

				}
				if (!std::cin.fail())
				{
					break;
				}
			}


			if (inputPointsH  < 0 || inputPointsH > pointsEasy)
			{
				std::cout << "Error input.\n";
				c();
			}
			else if (((inputPointsH)+myp2.getDefense()) > 20)
			{
				std::cout << "Error, goes past max stat.\n";
				c();
			}
			while (inputPointsH > pointsEasy || (((inputPointsH)+myp2.getDefense()) > 20))
			{
				std::cout << "How many points  towards defense?\n";
				std::cout << "You have " << pointsEasy << " left. \n";

				std::cin >> inputPointsH;
				std::cin.ignore();



				while (1)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("cls");
						cout << "You have entered the wrong input\n\n";
						c();
						std::cout << "How many points towards Defense?\n";
						std::cout << "You have " << inputPointsH << " left. \n";


						std::cin >> inputPointsH;

					}
					if (!std::cin.fail())
					{
						break;
					}
				}

				if (inputPointsH  < 0 || inputPointsH > pointsEasy)
				{
					std::cout << "Error input.\n";
					c();
				}
				else if (((inputPointsH)+myp2.getDefense()) > 20)
				{
					std::cout << "Error, goes past max stat.\n";
					c();
				}


			}

			pointsEasy -= inputPointsH;
			myp2.setDefense(myp2.getDefense() + (inputPointsH));
			c();



		}

		else if (input == 4)
		{
			std::cout << "You chose Speed.\n";
			c();

			std::cout << "How many points  towards speed?\n";
			std::cout << "You have " << pointsEasy << " left. \n";

			std::cin >> inputPointsH;
			std::cin.ignore();



			while (1)
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("cls");
					cout << "You have entered the wrong input\n\n";
					c();
					std::cout << "How many points towards Speed?\n";
					std::cout << "You have " << inputPointsH << " left. \n";


					std::cin >> inputPointsH;

				}
				if (!std::cin.fail())
				{
					break;
				}
			}


			if (inputPointsH  < 0 || inputPointsH > pointsEasy)
			{
				std::cout << "Error input.\n";
				c();
			}
			else if (((inputPointsH)+myp2.getSpeed()) > 20)
			{
				std::cout << "Error, goes past max stat.\n";
				c();
			}
			while (inputPointsH > pointsEasy || (((inputPointsH)+myp2.getSpeed()) > 20))
			{
				std::cout << "How many points  towards speed?\n";
				std::cout << "You have " << pointsEasy << " left. \n";

				std::cin >> inputPointsH;
				std::cin.ignore();


				while (1)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("cls");
						cout << "You have entered the wrong input\n\n";
						c();
						std::cout << "How many points towards Speed?\n";
						std::cout << "You have " << inputPointsH << " left. \n";


						std::cin >> inputPointsH;

					}
					if (!std::cin.fail())
					{
						break;
					}
				}


				if (inputPointsH  < 0 || inputPointsH > pointsEasy)
				{
					std::cout << "Error input.\n";
					c();
				}
				else if (((inputPointsH)+myp2.getSpeed()) > 20)
				{
					std::cout << "Error, goes past max stat.\n";
					c();
				}

			}

			pointsEasy -= inputPointsH;
			myp2.setSpeed(myp2.getSpeed() + (inputPointsH));
			c();

		}

		else if (input <= 0 || input >= 2)
		{
			std::cout << "Error input.\n";
			c();
		}


	}
	
	return myp2;
}
Player enemyDamage(Player myp, std::vector<Enemy*> enemies)
{

	for (auto range : enemies)
	{
		int rng = grng(7);
		float defenseMod = .5;

		if (rng > 0)
		{
			float enemyDamage = ((range->attack() - (myp.getDefense() * defenseMod)));
			if (enemyDamage < 0)
			{
				enemyDamage = 0;
			}
			std::cout << range->getName() << " attacks! \n"
				<< "They do " << enemyDamage << " damage! \n";
			myp.setHealth(myp.getHealth() - enemyDamage); // makes you loose health
		}
		else
		{
			cout << "Enemy missed..." << endl;
		}
		
		
	}
	c();
	return myp;
}
std::vector<Enemy*>  playerDamage(std::vector<Enemy*> enemies, Player & myp, Weapon w)
{
	
	w = myp.getCurrentW();
	std::cout << "You attack with " << w.getName() << "\n";
	int damage = w.getDamage() + myp.getAttack(); // determines damage

		int critChance = 15;
		int crit = grng(critChance) + 1;

	for (auto range : enemies) // a weird type of for loop that is used for vecotrs i thnk
	{
		if (crit == 4)
		{
			damage = damage * 2;
			std::cout << "Critical strike!\n";
		}
		std::cout << "You do " << damage << " damage!\n\n";
		//std::cout << range->getHealth() << std::endl << std::endl;
		range->setHealth(range->getHealth() - damage); // sets health to health - damage

		if (range->getHealth() <= 0)
		{
			std::cout << "Enemy Defeated!\n";

			myp.setGold(myp.getGold() + range->getGold());
			std::cout << "Obtained " << range->getGold() << " gold!\n";
			enemies.pop_back(); // if enemy dies delete enemy from the vector and break

			break;
		}
	}

	c();
	return enemies;

}
Player equipWeapon(Player myp)
{
	unsigned int weapon = 0;
	do
	{
		system("cls");
		myp.checkInventory();
		std::cout << "Choose a weapon.\n";
		std::cin >> weapon;
		std::cin.ignore();

		while (1)
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "You have entered the wrong input\n\n";
				c();

				myp.checkInventory();
				std::cout << "Choose a weapon.\n";
				std::cin >> weapon;

			}
			if (!std::cin.fail())
			{
				break;
			}
		}
	} while (weapon < 1 || weapon > myp.getAllWeapons().size());

	myp.setCurrentW(myp.getInventory(weapon - 1)); // sets your weapon to users choice
	Weapon temp = myp.getCurrentW();

	std::cout << "You equipped " << myp.getCurrentW().getName() << ".\n";  // shows you what you selected

	myp.setCurrentIndex(weapon - 1);
	myp.setAtFunction(myp.getCurrentIndex(), temp);
	c();
	return myp;
}
int battleSequence(std::vector<Enemy*> enemies, Player& myp, std::vector<Weapon> baseWeapons, Weapon w)
{
	int chance = 0;
	int realamm = myp.getCurrentW().getAmmo();
	int chanceFlare = 16;
	bool playerFirst = false;

	do // battle sequence //**********************************************************************************************
	{
		int options = 0;
		int run = grng(100);
		
		std::cout << "Your Health: " << myp.getHealth() << std::endl;
		std::cout << "Enenmy Health: ";
		for (auto range : enemies) { std::cout << range->getHealth() << std::endl << std::endl; }

		do
		{
			std::cout << "Fight or run?\n1) Fight\n2) Run\n3) Switch Weapon\n";
			std::cin >> options;
			//cin.ignore();
			options = inputValidation(options, "Fight or run?\n1) Fight\n2) Run\n3) Switch Weapon\n");
			c();
		} while (options < 1 || options > 3);


		if (options == 2)
		{
			int speedcheck = myp.getSpeed() * 3.5;
			//if (myp.getSpeed() < enemies.at(0)->getSpeed()) // 50% chance if u are slower
			//{
			//	speedCheck = 0
			//}
			//else // 66% chance if you are faster
			//{
			//	speedCheck = myp.getSpeed();
			//}
			if (speedcheck > run)
			{
				std::cout << "You ran away successfully!\n\n";
				c();
				enemies.pop_back();
				return 1;
			}
			else
			{
				std::cout << "You can't escape!\n\n";
				c();
				myp = enemyDamage(myp,enemies);
				if (myp.getHealth() <= 0)
				{
					over(); // ends game if you die
					c();
					return 0;
				}
			}
		}
		else if (options == 3)
		{
			myp = equipWeapon(myp);
			myp = enemyDamage(myp, enemies);
			if (myp.getHealth() <= 0)
			{
				over(); // ends game if you die
				c();
				return 0;
			}
			
		}
		else if (options == 1)
		{
			if ((!enemies.empty()) && (myp.getSpeed() < enemies.at(0)->getSpeed()))
			{
				myp = enemyDamage(myp, enemies);
				if (myp.getHealth() <= 0)
				{
					over(); // ends game if you die
					c();
					return 0;
				}
			}
			if (realamm == 0)
			{
				std::cout << "You ran out of ammo!\n";
				over();
				return 0;
			}
			if (w.getName().compare(baseWeapons.at(4).getName()) == 0) // this test to see if its a flare
			{													   // if it is, then you run an rng to possibly win an early game
				chance = grng(chanceFlare) + 1;
				if (chance == 2)
				{
					std::cout << "Someone saw the flare!\n";
					std::cout << "You were rescued!\n";
					c();
					return 0;
				}
				else
				{
					std::cout << "No one came to help.\n";
					c();
					std::cout << "Flares: " << realamm << std::endl;

					realamm -= 1; // decreases the ammo
					
					Weapon temp = myp.getCurrentW();
					temp.setAmmo(realamm);
					myp.setCurrentW(temp);
					myp.setAtFunction(myp.getCurrentIndex(), temp);

					enemies = playerDamage(enemies, myp, w);
					myp = enemyDamage(myp, enemies);
					if (myp.getHealth() <= 0)
					{
						over(); // ends game if you die
						c();
						return 0;
					}
				}
			}
			else if (w.getName().compare(baseWeapons.at(4).getName()) != 0)
			{
				if (w.getName().compare("Shotgun") == 0)
				{
					std::cout << "Ammo: " << realamm - 1 << std::endl;

				}
				else if (w.getName().compare("Pistol") == 0)
				{
					std::cout << "Ammo: " << realamm - 1 << std::endl;
				}
				else if (w.getName().compare("Bow") == 0)
				{
					std::cout << "Arrows: " << realamm - 1 << std::endl;
				}

				realamm -= 1; // decreases the ammo

				Weapon temp = myp.getCurrentW();
				temp.setAmmo(realamm);
				myp.setCurrentW(temp);
				myp.setAtFunction(myp.getCurrentIndex(), temp);

				enemies = playerDamage(enemies, myp, w);

			
				if ((!enemies.empty()) && (myp.getSpeed() >= enemies.at(0)->getSpeed()))
				{
					myp = enemyDamage(myp, enemies);
					if (myp.getHealth() <= 0)
					{
						over(); // ends game if you die
						c();
						return 0;
					}
				}
			}
		} 
		
	}while (enemies.size() == 1);
	
	return 1;
} //************************************************************* ^^^ their turn **************************************** end battle

int main()
{
	std::vector <Weapon> baseWeapons;
	baseWeapons.push_back(Weapon("Shotgun", 40, 40, 6)); // name, damage, price, ammo
	baseWeapons.push_back(Weapon("Pistol", 30, 30, 9));
	baseWeapons.push_back(Weapon("Bat", 15, 25, -100));
	baseWeapons.push_back(Weapon("Sword", 20, 30, -101));
	baseWeapons.push_back(Weapon("Flare gun", 10, 10, 4)); //6, 9, , 4, 10
	baseWeapons.push_back(Weapon("Bow", 25, 25, 10));
	std::vector <Enemy*> enemies; // vector of pointers of type Enemy this is used to point to child classes
	int ans = 0; // user input for if they want to play

	do
	{
		std::string titlePrompt = "Project Nano \n1) Play \n2) Quit \n";
		cout << titlePrompt;
		std::cin >> ans;
		ans = inputValidation(ans, titlePrompt);

		if (ans == 1)
		{
			break;
		}
		else if (ans == 2)
		{
			return 0;
		}
		else
		{
			std::cout << "Error\n";
			c();
		}
	} while (ans != 2 && ans != 1);

	system("cls");
	std::string name;
	std::cin.ignore();
	std::cout << "What is your name?\n";
	getline(cin, name);
	c();
	Player myp; // player class instantiated
	myp = setStats(baseWeapons);
	myp.setName(name);
	myp.checkStats();
	AmmoReserve amm;
	amm.arrows = 0;
	amm.flares = 0;
	amm.pistolAmmo = 0;
	amm.shotgunAmmo = 0;
	int rng6 = 6;
	int rand = grng(rng6);
	c();
	myp.setInvetory(baseWeapons.at(rand));
	std::cout << baseWeapons.at(rand).getName() << " obtained!" << std::endl;
	c();
	int counter = 1; // keeps track of days
	int MaxCounter = 14;

	if (myp.getDificulty() == 2)
	{
		MaxCounter = 21;
	}
	else if (myp.getDificulty() == 3)
	{
		MaxCounter = 28;
	}
	
	int h1, h2, h3;
	h1 = -100;
	h2 = -90;
	h3 = -80;
	int hunger = 0;
	if (myp.getDificulty() == 1)
	{
		hunger = h1;
	}
	else if (myp.getDificulty() == 2)
	{
		hunger = h2;
	}
	else if (myp.getDificulty() == 3)
	{
		hunger = h3;
	}

	std::string dummy = "";
	//**********************************************
	do
	{
		system("cls");int damageH = 25;
		int choice = 0; // action list choice
		std::cout << "Name: " << myp.getName() << "   "<< "Day: " << counter << "\t" << "Food Level: " << myp.getFood() << std::endl;
		actionList();
		std::cin >> choice;
		std::cin.ignore();

		while (1)//input validation for void propmt
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "You have entered the wrong input\n\n";
				c();

				actionList();
				std::cin >> choice;

			}
			if (!std::cin.fail())
			{
				break;
			}
		} 
	
		switch (choice) {
		case 1: // walk around
		{
			if (myp.getCurrentW().getPrice() == -1) // if weapon = -1 then it hasn't been assigned yet and it won't let you walk forward
			{
				std::cout << "You need to equip a weapon first.\n";

				c();
				break;
			}
			else
			{
				std::cout << "Day: " << counter << std::endl;
				std::cout << "You walk forward...\n";
				c();

				int spawn = 0; // keeps track of randomly generated result of walking forward
				int spawnChance = 10;
				spawn = grng(spawnChance) + 1;

				if (spawn > 7) // % chance of enemy spawing
				{
					enemies.push_back(enemySpawn()); // puts new enemy in a vector
					std::cout << std::endl;
					{
						int survive = battleSequence(enemies, myp, baseWeapons, myp.getCurrentW());

						if (survive == 0)
						{
							enemies.pop_back();
							c();
							return 0;
						}
						enemies.pop_back();

					}
				}
				else if (spawn == 2) // 20% chance of nothing hapening
				{
					std::cout << "Building found!\n";
					std::cout << "You slept for 3 days...\n";
					c();
					counter += 2;
					int rng3 = 6;

					if (grng(rng3) < 2)
					{
						enemies.push_back(enemySpawn3()); // puts new enemy in a vector
						std::cout << std::endl;
						{
							int survive = battleSequence(enemies, myp, baseWeapons, myp.getCurrentW());
							if (survive == 0)
							{
								enemies.pop_back();
								c();
								return 0;
							}
							else
								enemies.pop_back();

						}
					}
				}
				else if (spawn == 6)
				{
					std::cout << "Merchant appears.\n";
					c();
					int choice3;
					do
					{
						int medkitC = 40;
						int medkitH = 100;
						int foodC = 15;
						bool enufgold1 = true;
						bool enufgold2 = true;
						bool enufgold3 = true;

						int rng6 = 6;
						int newrand = grng(rng6);

						std::cout << "Would you like to purchace something?\n";
						std::cout << "Gold: " << myp.getGold() << std::endl;
						std::cout << "1) Medkit - " << medkitC << " gold\n"
							<< "2) " << baseWeapons[newrand].getName() << " - " << baseWeapons[newrand].getPrice() << " gold\n"
							<< "3) Food - "<<  foodC << " gold\n"
							<< "4) Exit\n";
						std::cin >> choice3;
						c();

						do
						{
							if (choice3 < 1 || choice3 > 4)
							{
								std::cout << "Would you like to purchace something?\n";
								std::cout << "Gold: " << myp.getGold() << std::endl;
								std::cout << "1) Medkit - 50 gold\n"
									<< "2) " << baseWeapons[newrand].getName() << " - 25 gold\n"
									<< "3) Food - 10 gold\n"
									<< "4) Exit\n";
								std::cin >> choice3;
								c();

							}

							if (choice3 == 1 && myp.getGold() < medkitC)
							{
								std::cout << "You don't have enough!\n";

								enufgold1 = false;
								c();
								break;
							}
							else if (choice3 == 2 && myp.getGold() < baseWeapons[newrand].getPrice())
							{
								std::cout << "You don't have enough!\n";
								enufgold2 = false;
								c();
							}
							else if (choice3 == 3 && myp.getGold() < foodC)
							{
								std::cout << "You don't have enough!\n";
								enufgold3 = false;
								c();
							}

							
						} while (choice3 < 1 || choice3 >4);


						if (choice3 == 1 && enufgold1 == true)
						{


							std::cout << "Thank you...\n";
							std::cout << "Obtained Medkit!\n";

							myp.setGold(myp.getGold() - medkitC);
							myp.setHealth(myp.getHealth() + medkitH);
							if (myp.getHealth() > 200)
							{
								myp.setHealth(200);
							}
							c();


						}
						else if (choice3 == 2 && enufgold2 == true)
						{
							std::cout << "Thank you...\n";
							std::cout << "Obtained " << baseWeapons[newrand].getName() << "! \n";

							myp.setGold(myp.getGold() - baseWeapons[newrand].getPrice());
							myp.setInvetory(baseWeapons[newrand]);
							c();

							if (baseWeapons[newrand].getName() == "Shotgun")
							{
								int latest = myp.getAllWeapons().size() - 1;
								Weapon temp1 = myp.getAddressOfVector().at(latest);

								temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().shotgunAmmo); // adds excess ammo to recent weapon
								amm.shotgunAmmo = 0; // sets the local excess ammo to 0 //this var might be redundant
								myp.setAmmoExcess(amm); // sets the player excess ammo to 0
								myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
								break;
							}

							if (baseWeapons[newrand].getName() == "Pistol")
							{
								int latest = myp.getAllWeapons().size() - 1;
								Weapon temp1 = myp.getAddressOfVector().at(latest);

								temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().pistolAmmo); // adds excess ammo to recent weapon
								amm.pistolAmmo = 0; // sets the local excess ammo to 0 //this var might be redundant
								myp.setAmmoExcess(amm); // sets the player excess ammo to 0
								myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
								break;
							}

							if (baseWeapons[newrand].getName() == "Flare gun")
							{
								int latest = myp.getAllWeapons().size() - 1;
								Weapon temp1 = myp.getAddressOfVector().at(latest);

								temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().flares); // adds excess ammo to recent weapon
								amm.flares = 0; // sets the local excess ammo to 0 //this var might be redundant
								myp.setAmmoExcess(amm); // sets the player excess ammo to 0
								myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
								break;
							}

							if (baseWeapons[newrand].getName() == "Bow")
							{
								int latest = myp.getAllWeapons().size() - 1;
								Weapon temp1 = myp.getAddressOfVector().at(latest);

								temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().arrows); // adds excess ammo to recent weapon
								amm.arrows = 0; // sets the local excess ammo to 0 //this var might be redundant
								myp.setAmmoExcess(amm); // sets the player excess ammo to 0
								myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
								break;
							}
							c();
						}
						else if (choice3 == 3 && enufgold3 == true)
						{
							std::cout << "Thank you...\n";
							std::cout << "Obtained Food! \n";
							myp.setGold(myp.getGold() - foodC);
							std::cout << "(Health increased by 10)\n"
								<< "Food level increased\n";
							c();
							myp.setFood(myp.getFood() + 20);
							myp.setHealth(myp.getHealth() + 10); // increases health and food
						}

						if (choice == 1 && !enufgold1)
						{
							break;
						}

					} while (choice3 != 4);

				}
				else if (spawn == 1) //  chance of small health pack being found
				{
					std::cout << "Day: " << counter << std::endl;
					std::cout << "Found a health pack!\n"
						<< "(Health increased by 20)\n";
					c();
					myp.setHealth(myp.getHealth() + 20);
				}
				else if (spawn == 4) 
				{
				std::cout << "Found nothing...\n"; 
				std::cout << "(10 damage taken from exhaustion)\n";
				c();
				myp.setHealth(myp.getHealth() - 10);
				}
				else
				{
					std::cout << "Day: " << counter << std::endl;
					std::cout << "Nothing happened.\n";
					c();
				}
				counter++; // when day passes
				if (myp.getFood() <= hunger)
				{
					std::cout << "\nYou took " << damageH << " damage from  hunger.\n";
					myp.setHealth(myp.getHealth() - damageH);
					c();
				}
			}
		}
		break;
		case 2: // equip weapon
		{
			myp.setFood(myp.getFood() + 10);
			myp = equipWeapon(myp);
		}
		break;
		case 3: // checks stats 
		{
			myp.setFood(myp.getFood() + 10);
		
			myp.checkStats();
			c();
		}
		break;
		case 4: // investigate
		{
			if (myp.getCurrentW().getAmmo() == -1) // if weapon = -1 then it hasn't been asigned yet and it won't let you walk forward
			{
				std::cout << "You need to equip a weapon first.\n";
				c();
				break;
			}

			int gamble = 0;
			int gambleChance = 13;
			gamble = grng(gambleChance);
			 
			if (gamble < 4)
			{
				food(myp);
			}
			else if (gamble == 6 || gamble == 8) // needs to be optimized
			{
				int rngAmmo = 4;
				int coiner = grng(rngAmmo);
				bool preesent = true;
				bool preesent1 = true;
				bool preesent2 = true;
				bool preesent3 = true;

				if (coiner == 0)
				{

					std::cout << "You found shotgun ammo!\n";
					c();
					for (unsigned int i = 0; i < myp.getAllWeapons().size(); i++)
					{

						if (myp.getCurrentW().getName().compare("Shotgun") == 0) // add to curr shotgun
						{
							Weapon temp = myp.getCurrentW();

							temp.setAmmo(temp.getAmmo() + 3);
							myp.setCurrentW(temp);
							myp.setAtFunction(myp.getCurrentIndex(), temp);
							preesent = true;
							break;
						}
						if (myp.getInventory(i).getName().compare("Shotgun") == 0) // add to inventory shotgun
						{
							Weapon temp = myp.getCurrentW(); //temporary holds current weapon;
							Weapon fake = myp.getInventory(i);// temp holds current index

							myp.setCurrentW(fake);
							fake.setAmmo(fake.getAmmo() + 3);
							myp.setCurrentW(fake);
							myp.setAtFunction(i, fake);

							myp.setCurrentW(temp);

					
							preesent = true;
							
							break;
						}
						 if (i == myp.getAllWeapons().size()-1)
						{
							preesent = false;
						}
					}
					if (preesent == false)
					{
						amm.shotgunAmmo += 3;
						myp.setAmmoExcess(amm);

					}
				}
				else if (coiner == 1)
				{
					std::cout << "You found pistol ammo!\n";
					c();
					for (unsigned int i = 0; i < myp.getAllWeapons().size(); i++)
					{

						if (myp.getCurrentW().getName().compare("Pistol") == 0)
						{

							Weapon temp = myp.getCurrentW();

							temp.setAmmo(temp.getAmmo() + 4);
							myp.setCurrentW(temp);
							myp.setAtFunction(myp.getCurrentIndex(), temp);
							preesent1 = true;
							break;
						}
						if (myp.getInventory(i).getName().compare("Pistol") == 0)
						{
							Weapon temp = myp.getCurrentW(); //temporary holds current weapon;
							Weapon fake = myp.getInventory(i);// temp holds current index

							myp.setCurrentW(fake);
							fake.setAmmo(fake.getAmmo() + 4);
							myp.setCurrentW(fake);
							myp.setAtFunction(i, fake);

				
							myp.setCurrentW(temp);

							
							preesent1 = true;
							break;
						}
						if (i == myp.getAllWeapons().size() - 1)
						{
							
							preesent1 = false;
						}
					}
					if (preesent1 == false)
					{

						amm.pistolAmmo += 4;
						myp.setAmmoExcess(amm);

					}
				}
				else if (coiner == 2)
				{
					std::cout << "You found flares!\n";
					c();
					for (unsigned int i = 0; i < myp.getAllWeapons().size(); i++)
					{

						if (myp.getCurrentW().getName().compare("Flare gun") == 0)
						{
							Weapon temp = myp.getCurrentW();

							temp.setAmmo(temp.getAmmo() + 2);
							myp.setCurrentW(temp);
							myp.setAtFunction(myp.getCurrentIndex(), temp);
							preesent2 = true;
							break;
						}
					 if (myp.getInventory(i).getName().compare("Flare gun") == 0)
						{
						 Weapon temp = myp.getCurrentW(); //temporary holds current weapon;
						 Weapon fake = myp.getInventory(i);// temp holds current index

						 myp.setCurrentW(fake);
						 fake.setAmmo(fake.getAmmo() + 2);
						 myp.setCurrentW(fake);
						 myp.setAtFunction(i, fake);

						
						 myp.setCurrentW(temp);

		
							preesent2 = true;
						
							break;
						}
						if (i == myp.getAllWeapons().size() - 1)
						{
						
							preesent2 = false;
						}
					}
					if (preesent2 == false)
					{

						amm.flares += 2;
						myp.setAmmoExcess(amm);

					}
				}
				else if (coiner == 3)
				{
					std::cout << "You found arrrows!\n";
					c();
					for (unsigned int i = 0; i < myp.getAllWeapons().size(); i++)
					{

						if (myp.getCurrentW().getName().compare("Bow") == 0)
						{
							Weapon temp = myp.getCurrentW();

							temp.setAmmo(temp.getAmmo() + 5);
							myp.setCurrentW(temp);
							myp.setAtFunction(myp.getCurrentIndex(), temp);
							preesent3 = true;
							break;
						}
					 if (myp.getInventory(i).getName().compare("Bow") == 0)
						{
							Weapon temp = myp.getCurrentW(); //temporary holds current weapon;
							Weapon fake = myp.getInventory(i);// temp holds current index

							myp.setCurrentW(fake);
							fake.setAmmo(fake.getAmmo() + 5);
							myp.setCurrentW(fake);
							myp.setAtFunction(i, fake);

							
							myp.setCurrentW(temp);

						
							
							preesent3 = true;
							break;
						}
						if (i == myp.getAllWeapons().size() - 1)
						{
			
							preesent3 = false;
						}
					}
					if (preesent3 == false)
					{


						amm.arrows += 5;
						myp.setAmmoExcess(amm);

					}
				}
			} 
			else if (gamble == 9 || gamble == 5)
			{
			int weaponChance = 6;
			int newW = 0;
			newW = grng(weaponChance);
				myp.setInvetory(baseWeapons[newW]); // pushes back new element to vector
				std::cout << baseWeapons[newW].getName() << " obtained!" << std::endl;
				c();

				 if (baseWeapons[newW].getName() == "Shotgun")
				{
					int latest = myp.getAllWeapons().size() - 1;
					Weapon temp1 = myp.getAddressOfVector().at(latest);
					
					temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().shotgunAmmo); // adds excess ammo to recent weapon
					amm.shotgunAmmo = 0; // sets the local excess ammo to 0 //this var might be redundant
					myp.setAmmoExcess(amm); // sets the player excess ammo to 0
					myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
					break;
				}

			if (baseWeapons[newW].getName() == "Pistol")
				{
					int latest = myp.getAllWeapons().size() - 1;
					Weapon temp1 = myp.getAddressOfVector().at(latest);

					temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().pistolAmmo); // adds excess ammo to recent weapon
					amm.pistolAmmo = 0; // sets the local excess ammo to 0 //this var might be redundant
					myp.setAmmoExcess(amm); // sets the player excess ammo to 0
					myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
					break;
				}

			 if (baseWeapons[newW].getName() == "Flare gun")
				{
					int latest = myp.getAllWeapons().size() - 1;
					Weapon temp1 = myp.getAddressOfVector().at(latest);

					temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().flares); // adds excess ammo to recent weapon
					amm.flares = 0; // sets the local excess ammo to 0 //this var might be redundant
					myp.setAmmoExcess(amm); // sets the player excess ammo to 0
					myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
					break;
				}

			if (baseWeapons[newW].getName() == "Bow")
				{
					int latest = myp.getAllWeapons().size() - 1;
					Weapon temp1 = myp.getAddressOfVector().at(latest);

					temp1.setAmmo(temp1.getAmmo() + myp.getAmmoExcess().arrows); // adds excess ammo to recent weapon
					amm.arrows = 0; // sets the local excess ammo to 0 //this var might be redundant
					myp.setAmmoExcess(amm); // sets the player excess ammo to 0
					myp.setAtFunction(latest, temp1); // updates the player's weapon vector with the new ammo for recent weapon
					break;
				}
				c();

			}
			else if (gamble == 7)
			{

			int rng3 = 3;
			int statBoost = grng(rng3) + 1;

				if (statBoost == 1 && myp.getAttack() < 20)
				{
					std::cout << "You found an attack bonus!\n";
					std::cout << "Attack added to stat.\n";
					c();
					myp.setAttack(myp.getAttack() + 5);

					if (myp.getAttack() > 20)
					{
						myp.setAttack(20);
					}

				}
				else if (statBoost == 1)
				{
					std::cout << "Nothing Found\n"; c();
				}

				if (statBoost == 2 && myp.getDefense() < 20)
				{
					std::cout << "You found a defense bonus!\n";
					std::cout << "Defense added to stat.\n";
					c();
					myp.setDefense(myp.getDefense() + 5);

					if (myp.getDefense() > 20)
					{
						myp.setDefense(20);
					}
				}
				else if (statBoost == 2)
				{
					std::cout << "Nothing Found\n"; c();
				}

				if (statBoost == 3 && myp.getSpeed() < 20)
				{
					std::cout << "You found a speed bonus!\n";
					std::cout << "Speed added to stat.\n";
					c();
					myp.setSpeed(myp.getSpeed() + 5);

					if (myp.getSpeed() > 20)
					{
						myp.setSpeed(20);
					}
				}else if (statBoost == 3)
				{
					std::cout << "Nothing Found\n"; c();
				}
				

			
				c();
			}
			else if (gamble == 10)
			{
				enemies.push_back(enemySpawn2()); // puts new enemy in a vector
				std::cout << std::endl;
				{
					int survive = battleSequence(enemies, myp, baseWeapons, myp.getCurrentW());

					if (survive == 0)
					{
						enemies.pop_back();
						c();
						return 0;
					}
					enemies.pop_back();

				}
			}
			else
			{
				enemies.push_back(enemySpawn()); // puts new enemy in a vector
				std::cout << std::endl;
				{

					int survive = battleSequence(enemies, myp, baseWeapons, myp.getCurrentW());
					if (survive == 0)
					{
						enemies.pop_back();
						c();
						return 0;
					}
					enemies.pop_back();

				}
			}
			counter++;
			if (myp.getFood() <= hunger)
			{
				std::cout << "\nYou took " << damageH << " damage from  hunger.\n";
				myp.setHealth(myp.getHealth() - damageH);
				c();
			}
		}
		break;
		case 5: // forage
		{
			int forageChance = 12;
			int foodz = grng(forageChance);

			if (foodz <= 5)
			{
				food(myp);
			}
			else if (foodz > 5 && foodz <= 8)
			{
				food(myp);
				std::cout << "You were injured looking for food...\n";
				std::cout << "(You took 25 damage)\n";
				myp.setHealth(myp.getHealth() - 25);
				c();
			}
			else
			{
				std::cout << "Nothing found...\n";
				std::cout << "You were injured looking for food...\n";
				std::cout << "(You took 25 damage)\n";
				myp.setHealth(myp.getHealth() - 25);
				c();
			}
			counter++;
		}
		break;
		case 6: // check ammo and weapons
		{
			myp.setFood(myp.getFood() + 10);
			myp.getWeaponAmmo();
			c();
		}
		break;
		case 7: // ends game
		{
			return 0;
		}
		break;
		}

		myp.setFood(myp.getFood() - 10); // after every day, you loose 10 hunger points
		if (myp.getFood() < hunger)
		{
			myp.setFood(hunger);
		}
	} while (myp.getHealth() > 0 && counter <= MaxCounter); // if you survive you win

	if (myp.getHealth() <= 0)
	{
		over(); c(); return 0;
	}
	std::cout << "Help finally came!\n";
	std::cout << "You win.\n";
	c();
	return 0;
}