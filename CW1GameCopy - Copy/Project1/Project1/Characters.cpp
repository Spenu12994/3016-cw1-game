#include <iostream>//cin cout
#include <stdlib.h>//rand
#include <conio.h>
#include <ctime>//clock(),CLOCKS_PER_SEC
#include <string>
#include <random>
using namespace std;

//hierarchy: (parent: children)
//^ fighter
//^ fighter: player, enemy
//^ enemy: beast, humanoid
//^ beast: wolf,
//^ humanoid: skeleton



class Fighter {
public:
	Fighter(int att, int spe, int hea, string typ, string nam) {//constructor
		health = hea;
		maxHealth = health;
		speed = spe + ((level * 1));
		attack = att + ((level * 1));
		type = typ;
		name = nam;
	}

	Fighter() {//default constructor
		health = 20;
		maxHealth = 20;
		speed = 20;
		attack = 20;
		type = "Null";
		name = "Null";
	}

	void heal() {
		health = maxHealth;
	}


	void setName() {//Let player choose their name
		system("cls");//clear screen
		bool nameSet = false;//set name is false
		string ChosenName = "";//chosen name string variable
		while (nameSet == false) {//while loop until our name is chosen
			try {
				cout << "Please Select Your Name :";
				cin >> ChosenName;
				if (ChosenName.length() <= 0) {//short/negative name
					throw string("Name is Too short");//throw short name to catch
				}
				else if (ChosenName.length() >= 30) {//long name
					throw string("Name is Too long, Please keep below 30 characters");//throw long name to catch
				}
				//welcome player
				cout << "Welcome " << ChosenName;
				name = ChosenName;//set name
				nameSet = true;//exit loop
			}
			catch (string e) {//catch thrown strings
				cout << "Error occured (" << e << ")\n Please Press any button to retry...";
				_getch();//pause playback to show error message
				system("cls");//clear screen
				break;
			}
			catch (exception e) {//catch unexpected errors
				cout << "Unexpected Error occured (" << e.what() << ")\n Please Press any button to retry...";
				_getch();//pause playback to show error message
				system("cls");//clear screen
				break;
			}
		}
	}

	void printStats() {//Print out our stats in the battle menu
		
		cout << "####################" << endl << "# " << name;
		for (int i = 0; i < (17 - name.length()); i++) {//create each line equal length
			cout << " ";
		}
		cout << "#" << endl;

		cout << "# Health:          #" << endl;

		cout << "# [";


		float perentageHealth = (((float)health / (float)maxHealth) * 100);//cast to floats to avoid integer division
		int maxNum = 100;
		if (perentageHealth < 10 and perentageHealth > 0) {
			cout << char(177);
			maxNum = maxNum - 10;
		}
		for (int i = 10; i < maxNum; i = i+10) {//create each line equal length
			if (i <= perentageHealth) {
				cout << char(178);
			}
			else {
				cout << " ";
			}
		}
		cout << "]";
		for (int i = 0; i <= 5; i++) {//create each line equal length
			cout << " ";
		}
		cout << "#" << endl << "#                  #" << endl << "####################" << endl;
		
	}

	void takeDamage(int damage) {
		cout << "..." << endl;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(1, 100);
		int ranNumber = dist(mt);
		if (ranNumber < speed) {
			cout << "It Missed!" << endl;
		}
		else {
			cout << name << " took " << damage << " Damage!" << endl;
			setHealth(health - damage);
		}
	}


	void reduceSpeed(int spe) {//reduce our speed stat
		cout << name << "'s Speed Dropped!" << endl;
		speed = speed - spe;
		if (speed <= 5) {//make sure speed doesnt go into obsolete or negative values
			speed = 5;
		}
	}

	void reduceAttack(int att) {//reduce our attack stat
		cout << name << "'s Attack Dropped!" << endl;
		attack = attack - att;
		if (attack <= 5) {//make sure attacks dont go into obsolete or negative values (healling the player(found from bug-testing)
			attack = 5;
		}
	}

	virtual int AttackEnemy() {//virtual function to attack and enemy
		if (type == "Humanoid") {
			cout << endl << "The Fighter Slashes!" << endl;
		}
		else if (type == "Beast") {
			cout << endl << "The Beast Bites!" << endl;
		}
		else if (type == "Human") {
			cout << endl << "You Swing!" << endl;
		}

		return((attack * 0.5) + (level * 5));
	}

	virtual void Idle() {
		cout << "The " + name + " Stands By.." << endl;
	}
		

	//Return Values
	int getHealth() {//public function to return health
		
		return health;
		
	}

	int getLevel() {
		return level;
	}

	int getMaxHealth() {//public function to return maxHealth
		
		return maxHealth;
		
	}
	string getName() {
		return name;
	}
	string getType() {
		return type;
	}

		private:

			void setHealth(int damage) {
				health = damage;
			}
protected:
	int health;
	int maxHealth;
	int level = 1;
	int speed;
	int attack;
	int speedPenalty = 0;
	int attackPenalty = 0;
	string type;
	string name;
};

class Player : public Fighter {
public:
	Player(int att, int spe, int hea, string typ, string nam, int xp, int lvl) :Fighter(att, spe, hea, typ, nam) {//Constructor
		exp = xp;
		level = lvl;
		maxHealth = (100 + (level * 50));
		if (hea >= maxHealth) {//make sure health is not above max health
			health = maxHealth;//if it is set it to max health
		}
		else {
			health = hea;//if not, set as passed variable
		}
	};

	void updateSave(string nam, int lvl, int xp, int helth) {//Update our object
		name = name;
		level = lvl;
		exp = xp;
		health = helth;
	}
	
	int AttackEnemy(int hitMultiplier) {//get our dmg done to an enemy
		cout << endl << hitMultiplier << "X Multiplier!" << endl;
		return((attack * 0.1) * hitMultiplier);
	}
	//methods for saveEngine to rewrite player:
	void resetFromSave(string namSave, int healthSave, int experienceSave, int lvlSave) {
		exp = experienceSave;
		level = lvlSave;
		maxHealth = (100 + ((level * 50)));
		if (healthSave >= maxHealth) {
			health = maxHealth;
		}
		else {
			health = (healthSave);
		}
		speed = 30 + ((lvlSave * 1));
		attack = 30 + ((lvlSave * 1));
		type = "Human";
		name = namSave;
	}

	void gainExp(int expr) {//function to gain exp
		cout << name << "Gained " << expr << " Experience!";
		exp = exp + expr;//increase our exp

		while(exp >= 1000) {//Have we leveled up?
			cout << "\n Leveled up! " << (level) << "->" << (level + 1) << endl;
			exp = exp - 1000;
			level = level + 1;
			//Increase Stats
			maxHealth = 100 + ((level * 50));
			health = health + (50);//add the difference between level ups to heal slightly on level up inline with level up boost
			speed = 50 + ((level * 1));
			attack = attack + ((level * 1));

		}
		
		cout << "\n Press Enter To Continue...";

		//wait for enter to increase readability
		while (_getch() != '\r') {

		}
	}
	int getExp() {
		return exp;
	}
	int getLevel() {
		return level;
	}
private:
	int exp;
	Player* playerPointer;
};

// Enemy Class
class Enemy : public Fighter {
public:
	Enemy(int spe, int att, int hea, string typ, string nam) : Fighter(att, spe, hea, typ, nam) {
	}
	
	virtual float special() { return 5; };
	virtual string specialType() { return "Attack"; };
};


// Enemy Types
class Beast : public Enemy {
public:
	Beast(int spe, int att, int hea, string nam, string typ = "Beast") : Enemy(spe, att, hea, typ, nam) {}
	string specialType() {
		cout << endl << "The Beast Roars!" << endl;
		return "Speed";
	};
	virtual float special() {

		return (speed * 0.1) + level;
	};

	virtual void Idle() {
		cout << "The " + name + " Beast Flinches.." << endl;
	}
};

//parent class for skeleton/humanoid enemies
class Humanoid : public Enemy {
public:
	Humanoid(int spe, int att, int hea, string nam, string typ = "Humanoid") : Enemy(spe, att, hea, typ, nam) {}

	string specialType() {//print our special text and return special //overwrited virtual function
		cout << endl << "The Fighter Blocks!" << endl;
		return "Attack";
	};

	virtual float special() {//return the power of our special

		return (speed * 0.1) + level;
	};

	void Idle() {//prints idle text, overwrites virtual function
		cout << "The " + name + " Fighter Hesitates.." << endl;
	}
};

//Demon Type
class Demonite : public Enemy {
public:
	Demonite(int spe, int att, int hea, string nam, string typ = "Demon") : Enemy(spe, att, hea, typ, nam) {}

	string specialType() {
		cout << endl << "The Demon Screeches!" << endl;
		return "Speed";
	};

	void Idle() {
		cout << "You Feel The Fires Of Hell Beneath Your Feet" << endl;
	}
};

//Enemy Varieties 
	// Beasts
class wolf : public Beast {
public:
	wolf(int spe = 35, int att = 10, int hea = 60, string nam = "Wolf") : Beast(spe, att, hea, nam) {
		level = 3;
	};

};


//Humanoids
class skeleton : public Humanoid {
public:
	skeleton(int spe = 20, int att = 30, int hea = 40, string nam = "Skeleton") : Humanoid(spe, att, hea, nam) {
		level = 2;
	};

};
//Demon Boss
class Demon : public Demonite {
public:
	Demon(int spe = 15, int att = 40, int hea = 200, string nam = "Demon Acolyte") : Demonite(spe, att, hea, nam) {
		level = 15;
	};
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



class Fight {//Class which handles the fight scenes with our player and enemies
public:
	Fight(Player* player, Enemy* enemies, int arrSize) {//constructor, (player pointers, array of enemies, and how many enemies are in the array)
		playerPointer = player;
		enemySize = arrSize;
		enemyPointer = enemies;
	}



	//~Fight() {
	//	delete playerPointer;
	//	delete enemyPointer;
	//	cout << "Destroyed";
	//}

	bool Status() {//gets battle statis
		if (playerPointer->getHealth() <= 0) {//player dies, update() will pick up on this
			delete enemyPointer;
			return false;
		}
		else if (enemyPointer->getHealth() <= 0) {//enemy dies
			cout << "You Win!" << endl;
			//reward exp
			int expTemp = (enemyPointer->getLevel() * 550);
			cout << "Gained " << expTemp << " EXP!" << endl;
			//gain exp to character
			playerPointer->gainExp(expTemp);
			//Delete our pointer
			delete enemyPointer;
			//_getch() so player can read text
			_getch();
			return false;//return false (fight loop can end)
		}
		else if (ran == true) {//if the player ran
			delete enemyPointer;//delete enemy
			return false;//return false (fight loop can end)
		}
		else {
			return true;//return true (fight hasnt ended)
		}
	}

	void startFight() {
		printFighters();
		
	}

	void battleTurn(int choice, int Arrows) {//take a turn in battle, player Move then Enemy Move
		//playerturn

		int total = 1;//damage multiplier for arrows minigame
		int damageDone = 0;//total damage done

		//initialising random number generator
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(1, 100);
		
		int ranNumber = dist(mt);//generate a random number
		int prevInt = 1;//previous arrow location so we dont choose the same arrow twice (increases readability)

		switch (choice) {//switch for our menu choice
		case 1://Fight
			
			for (int i = 0; i < Arrows; i++) {//for loop to throw as many arrows as is passed to method
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_real_distribution<double> dist(0, 3);//RNG betwee 0,1,2,3
				ranNumber = dist(mt);//generate number

				if (ranNumber == prevInt) {//if we have had this number already
					ranNumber = ranNumber - 1;//edit our arrow
					if (ranNumber < 0) {//keep within bounds
						ranNumber = ranNumber + 4;
					}

				}
				total = total + attackSystem(ranNumber);//total = total + (was the arrow pressed correctly? 1 or 0);
				prevInt = ranNumber;//previous number is our current iteration
			}
			damageDone = playerPointer->AttackEnemy(total);//damage done is, attack enemy with our final multiplier
			enemyPointer->takeDamage(damageDone);//get the enemy to take damage
			break;
		case 2://Special
			

			if (ranNumber < 50) {//Slow Speed
				enemyPointer->reduceSpeed(3 * playerPointer->getLevel());//lower speed based on level
				cout << "Reduced Enemy Speed by " << (3 * playerPointer->getLevel());
			}
			else {//Lower Attack
				enemyPointer->reduceAttack(3 * playerPointer->getLevel());//lower speed based on level
				cout << "Reduced Enemy Attack by " << (3 * playerPointer->getLevel());
			}
			break;
		case 3://Run
			if (enemyPointer->getType() != "Demon") {//if the enemy is a demon
				ran = true;//if enemy is not demon, run
			}
			else {//if enemy is demon
				cout << "Fire Engulfs the fields around you..." << endl << "Escape is not possible." << endl;// tell player they cant run
			}
			break;//end
		}

		//Enemy Turn
		cout << enemyPointer->getName() << "'s Turn!" << endl;
		if (ran != true) {//if we havent ran
			ranNumber = dist(mt);//random number
			if (ranNumber <= 70) {//Attack
				int dmg = enemyPointer->AttackEnemy();//get dmg done
				playerPointer->takeDamage(dmg);//make player take damage
			}
			else if (ranNumber > 70 and ranNumber <= 90) {//Special
				string specType = enemyPointer->specialType();//get special type
				if (specType == "Attack") {//if type attack, 
					int debuff = enemyPointer->special();//get number
					playerPointer->reduceAttack(debuff);//reduce attack by number
				}
				else if (specType == "Speed") {//if speed
					int debuff = enemyPointer->special();//get number
					playerPointer->reduceSpeed(debuff);//reduce attack by number
				}
			}
			else {//Nothing
				enemyPointer->Idle();//run idle function
			}

			cout << "Press enter to Continue..";//end of turn, press to continue
			while (_getch() != '\r') {//wait until enter is hit, so player can read text

			}
		}
	}

	void printFighters() {//print out fighter state
		system("cls");
		playerPointer->printStats();
		enemyPointer->printStats();
	}

	int Menu(int currKey, int menuNumTemp) {//method for viewing and interacting with fight menu // returns menu option chosen
		int menuNum = menuNumTemp;
		switch (currKey) {//switch keypress condition (char)
		case 2://left
			menuNum = menuNum - 1;
			if (menuNum < 1) {
				menuNum = menuNum + 3;
			}
			break;
		case 4://right
			menuNum = menuNum + 1;
			if (menuNum > 3) {
				menuNum = menuNum - 3;
			}
			break;

		case 6:
			switch (menuNum) {
				case 1://Fight
					battleTurn(1, 4);
					break;
				case 2://Special
					battleTurn(2, 4);
					break;
				case 3://Run
					battleTurn(3, 4);
					break;
			}
		}
		printFighters();

		switch (menuNum) {
		case 1://Fight
			cout << endl << " Fight[@] Special[] Run[]";
			break;
		case 2://Fight
			cout << endl << " Fight[] Special[@] Run[]";
			break;
		case 3://Fight
			cout << endl << " Fight[] Special[] Run[@]";
			break;
		}
		return menuNum;
	}

	void printArrow(int num) {//print out arrows for our fighting gameplay
		switch (num) {
		case 0://up
			cout << "\n     ." << "\n   .:;:." << "\n .:;;;;;:." << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   : ;;;" << "\n     ;:;" << "\n   . :.;" << "\n     . :" << "\n   .   ." << "\n      .";
			break;
		case 1://down
			cout << "\n     ." << "\n       ." << "\n   . ;." << "\n    .;" << "\n     ;;." << "\n   ;.;;" << "\n   ;;;;." << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n ..;;;;;.." << "\n  ':::::'" << "\n    ':`";
			break;
		case 2://right
			cout << "\n                  ." << "\n   .. ............;;." << "\n    ..::::::::::::;;;;." << "\n  . . ::::::::::::;;:'" << "\n                  :'";
			break;
		case 3://left
			cout << "\n       ." << "\n     .;;............ .." << "\n   .;;;;::::::::::::.." << "\n    ':;;:::::::::::: . ." << "\n      ':";
			break;
		}
	}

	int attackSystem(int randomInt) {//method for the fighting minigame, section will run the game, then return how many attacks were blocked

		int delay = 1;//delay (in seconds) between our attacks
		char key;//our key pressed
		delay *= CLOCKS_PER_SEC;//convert our seconds delay into clocks

		clock_t now = clock();//set a clock
		bool pressed = false;//define button pressed to false


		system("cls");//clear the screen
		cout << "Attack!" << endl;
		printArrow(randomInt);//print an arrow in the direction chosen
		
		while (clock() - now < delay) {//while our delay isnt up
			
			if (_kbhit()) {//if a button is hit
				key = _getch();//save the button hit as char
				pressed = true;//say pressed is true
			}
		}

		if (pressed) {//if a button was pressed...
			//check it is the right button
			switch (key) {//switch for our pressed button
			case 'H'://up
			case 'w':
				if (randomInt == 0) {//if the button pressed matches the arrow's direction...
					
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'P'://down
			case 's':
				if (randomInt == 1) {//if the button pressed matches the arrow's direction...
					
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'M'://right
			case 'd':
				if (randomInt == 2) {//if the button pressed matches the arrow's direction...
					
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'K'://left
			case 'a':
				if (randomInt == 3) {//if the button pressed matches the arrow's direction...
					
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			default://if none of the correct buttons were hit
				cout << "\n Missed!" << key;//player missed
				return 0;
				break;
			}

		}
		else {//if no button was pressed
			cout << "\n not pressed in time";
			return 0;//return 0
		}
	}

private://private variables
	int enemySize;
	bool ran = false;
	Player* playerPointer;
	Enemy* enemyPointer;
};







/*int main() {
	Player playerChar;
	wolf wolfEne1;
	wolf wolfEne2;
	skeleton skeletonEne1;

	Fighter tempArray[] = { wolfEne1, wolfEne2, skeletonEne1 };
	Fighter* playerPointer = &playerChar;

	Fight currFight(playerPointer, tempArray, 3);

	currFight.printFighters();

	for (int i = 0; i < 4; i++) {
		currFight.printArrow(i);
	}
	while (true) {
		if (_getch() == 'm') {
			int total = 0;
			for (int i = 0; i < 4; i++) {
				total = total + currFight.attackSystem();
				cout << "\nBlocked " << total << "out of 4 attacks!\n";
			}
		}
	}
	return 0;
}*/