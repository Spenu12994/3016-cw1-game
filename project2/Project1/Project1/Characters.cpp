#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

//hierarchy: (parent: children)
//^ fighter
//^ fighter: player, enemy
//^ enemy: beast, humanoid
//^ beast: wolf,
//^ humanoid: skeleton


class Fighter {
public:
	Fighter(int att, int spe, int hea, string typ, string nam) {
		health = hea;
		speed = spe;
		attack = att;
		type = typ;
		name = nam;
	}

	void setStats() {

	}

	void setName() {
		system("cls");
		bool nameSet = false;
		string ChosenName = "";
		while (nameSet == false) {
			try {
				cout << "Please Select Your Name :";
				cin >> ChosenName;
				if (ChosenName.length() <= 0) {
					throw string("Name is Too short");
				}
				else if (ChosenName.length() >= 30) {
					throw string("Name is Too long, Please keep below 30 characters");
				}

				cout << "Welcome " << ChosenName;
				name = ChosenName;
				nameSet = true;
			}
			catch(string e){
				cout << "Error occured (" << e << ")\n Please Press any button to retry...";
				_getch();//pause playback to show error message
				system("cls");//clear screen
				break;
			}
			catch (exception e) {
				cout << "Unexpected Error occured (" << e.what() << ")\n Please Press any button to retry...";
				_getch();//pause playback to show error message
				system("cls");//clear screen
				break;
			}
		}
	}

	void printStats() {
		cout << name << endl;
		cout << "s:" << speed << endl;
		cout << "a:" << attack << endl;
		cout << "h:" << health << endl;
		cout << endl;
	}

	void takeDamage(int damage) {
		cout << "..." << endl;
		int ranNumber = (rand() % 100 + 1);
		if (ranNumber < speed) {
			cout << "It Missed!" << endl;
		}
		else {
			cout << name << " took " << damage << " Damage!" << endl;
			health = health - damage;
		}
	}

	void reduceSpeed(int spe) {
		cout << "Your Speed Dropped!" << endl;
		speed = speed - spe;
	}

	void reduceAttack(int att) {
		cout << "Your Attack Dropped!" << endl;
		attack = attack - att;
	}

	void AttackEnemy(Fighter enemy) {
		if (type == "Humanoid") {
			cout << endl << "The Fighter Slashes!" << endl;
		}
		else if (type == "Beast") {
			cout << endl << "The Beast Bites!" << endl;
		}
		else if (type == "Human") {
			cout << endl << "You Swing!" << endl;
		}

		enemy.takeDamage(attack * 0.1);
	}

protected:
	int health;
	int speed;
	int attack;
	string type;
	string name;
};

class Player : public Fighter {
public:
	Player(int att, int spe, int hea, string typ, string nam, int xp, int lvl) :Fighter(att, spe, hea, typ, nam) {
		exp = xp;
		level = lvl;
	}

	void gainExp(int expr) {
		cout << name << "Gained " << expr << " Experience!";
		exp = exp + expr;

		if (exp >= 1000) {
			cout << "\n Leveled up! " << (level) << "->" << (level + 1);
			exp - 1000;
			level = level + 1;
		}

		cout << "\n Press Enter To Continue...";

		while (getchar() != '\n');
	}

private:
	int exp;
	int level;
};

// Enemy Class
class Enemy : public Fighter {
public:
	Enemy(int spe, int att, int hea, string typ, string nam) : Fighter(att, spe, hea, typ, nam) {
	}

	virtual void special() {};
};


// Enemy Types
class Beast : public Enemy {
public:
	Beast(int spe, int att, int hea, string nam, string typ = "Beast") : Enemy(spe, att, hea, typ, nam) {}
	void special(Player playerObj) {
		cout << endl << "The Beast Roars!" << endl;
		playerObj.reduceAttack(5);
	};
};

class Humanoid : public Enemy {
public:
	Humanoid(int spe, int att, int hea, string nam, string typ = "Humanoid") : Enemy(spe, att, hea, typ, nam) {}
	void special(Player playerObj) {
		cout << endl << "The Fighter Blocks!" << endl;
		playerObj.reduceAttack(5);
	};
};


//Enemy Varieties 
	// Beasts
class wolf : public Beast {
public:
	wolf(int spe = 40, int att = 10, int hea = 25, string nam = "Wolf") : Beast(spe, att, hea, nam) {};

private:
	int speed = 20;
	int attack = 33;
	int health = 10;
};


//Humanoids
class skeleton : public Humanoid {
public:
	skeleton(int spe = 20, int att = 30, int hea = 10, string nam = "Skeleton") : Humanoid(spe, att, hea, nam) {};

private:
	int speed = 20;
	int attack = 30;
	int health = 10;
};

//int main() {
//	Player PlayerMan;
//
//	wolf enemyWolf;
//	skeleton enemySkeleton;
//
//
//	enemyWolf.printStats();
//	enemySkeleton.printStats();
//	enemyWolf.special(PlayerMan);
//	enemySkeleton.special(PlayerMan);
//
//	PlayerMan.AttackEnemy(enemyWolf);
//	PlayerMan.AttackEnemy(enemySkeleton);
//	enemyWolf.AttackEnemy(PlayerMan);
//	enemySkeleton.AttackEnemy(PlayerMan);
//
//
//
//	return 0;
//}
