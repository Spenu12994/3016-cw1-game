#include <iostream>
#include <stdlib.h>
using namespace std;

class Fighter {
public:
	Fighter(int att, int spe, int hea,string typ,string nam) {
		health = hea;
		speed = spe;
		attack = att;
		type = typ;
		name = nam;
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

class Player : public Fighter{
public:
	Player(int att = 30, int spe = 30, int hea = 100, string typ = "Human", string nam = "You") :Fighter(att, spe, hea, typ, nam) {}
};

// Enemy Class
class Enemy : public Fighter{
public:
	Enemy(int spe, int att, int hea, string typ, string nam) : Fighter(att,spe,hea,typ,nam) {
	}

	virtual void special() {};
};


// Enemy Types
class Beast : public Enemy {
public:
	Beast(int spe, int att, int hea, string nam, string typ = "Beast") : Enemy(spe, att, hea, typ,nam) {}
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

int main() {
	Player PlayerMan;

	wolf enemyWolf;
	skeleton enemySkeleton;
	

	enemyWolf.printStats();
	enemySkeleton.printStats();
	enemyWolf.special(PlayerMan);
	enemySkeleton.special(PlayerMan);

	PlayerMan.AttackEnemy(enemyWolf);
	PlayerMan.AttackEnemy(enemySkeleton);
	enemyWolf.AttackEnemy(PlayerMan);
	enemySkeleton.AttackEnemy(PlayerMan);



	return 0;
}