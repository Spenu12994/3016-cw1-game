#include <ctime>//clock(),CLOCKS_PER_SEC
#include <conio.h>//cin cout, etc
#include "Characters.cpp"//get our characters for the fight

class Fight {//Class which handles the fight scenes with our player and enemies
public:
	Fight(Player* player, Fighter enemies[], int arrSize) {//constructor, (player pointers, array of enemies, and how many enemies are in the array)
		playerPointer = player;
		enemySize = arrSize;
		enemyPointer = enemies;
	}

	//~Fight() {
	//	delete playerPointer;
	//	delete enemyPointer;
	//	cout << "Destroyed";
	//}

	void printFighters() {//print out fighter state
		playerPointer->printStats();
		for (int i = 0; i < (enemySize); i++) {
			(enemyPointer + i)->printStats();
		}
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

	int attackSystem() {//method for the fighting minigame, section will run the game, then return how many attacks were blocked

		int delay = 1;//delay (in seconds) between our attacks
		char key;//our key pressed
		delay *= CLOCKS_PER_SEC;//convert our seconds delay into clocks

		clock_t now = clock();//set a clock
		bool pressed = false;//define button pressed to false

		int randomInt = rand() % 4;//get the direction of our attack

		system("cls");//clear the screen

		printArrow(randomInt);//print an arrow in the direction chosen

		cout << "Attacking";//print that an attack is happening
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
					cout << "\nBlocked!";//tell the user it was blocked
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'P'://down
			case 's':
				if (randomInt == 1) {//if the button pressed matches the arrow's direction...
					cout << "\nBlocked!";//tell the user it was blocked
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'M'://right
			case 'd':
				if (randomInt == 2) {//if the button pressed matches the arrow's direction...
					cout << "\nBlocked!";//tell the user it was blocked
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			case 'K'://left
			case 'a':
				if (randomInt == 3) {//if the button pressed matches the arrow's direction...
					cout << "\nBlocked!";//tell the user it was blocked
					return 1;//return the attack was blocked
				}
				else {
					return 0;//arrow was missed, tell calling section that it blocked no attacks
				}
				break;
			default://if none of the correct buttons were hit
				cout << "\nMissed!" << key;//player missed
				return 0;
				break;
			}

		}
		else {//if no button was pressed
			cout << "\nnot pressed in time";
			return 0;//return 0
		}
	}

private://private variables
	int enemySize;
	Fighter* playerPointer;
	Fighter* enemyPointer;
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