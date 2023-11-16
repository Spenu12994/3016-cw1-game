#include "Character.cpp"
#include <ctime>
#include <conio.h>

class Fight{
public:
	Fight(Fighter *player, Fighter enemies[], int arrSize){
		playerPointer = player;
		enemySize = arrSize;
		enemyPointer = enemies;
	}

	//~Fight() {
	//	delete playerPointer;
	//	delete enemyPointer;
	//	cout << "Destroyed";
	//}

	void printFighters(){
		playerPointer->printStats();
		for (int i = 0; i < (enemySize); i++) {
			(enemyPointer + i)->printStats();
		}

	}
	void printArrow(int num) {
		switch (num) {
		case 0://up
			cout << "\n     ." << "\n   .:;:." << "\n .:;;;;;:." << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" <<"\n   : ;;;" <<"\n     ;:;"<<"\n   . :.;"<<"\n     . :"<<"\n   .   ."<<"\n      .";
			break;
		case 1://down
			cout << "\n     ." << "\n       ." << "\n   . ;." << "\n    .;" << "\n     ;;."<<"\n   ;.;;" << "\n   ;;;;."<< "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n   ;;;;;" << "\n ..;;;;;.." << "\n  ':::::'" << "\n    ':`";
			break;
		case 2://right
			cout << "\n                  ." << "\n   .. ............;;." << "\n    ..::::::::::::;;;;." << "\n  . . ::::::::::::;;:'" << "\n                  :'";
			break;
		case 3://left
			cout << "\n       ." << "\n     .;;............ .." << "\n   .;;;;::::::::::::.." << "\n    ':;;:::::::::::: . ." << "\n      ':";
			break;
		}
	}
	int attackSystem() {
		
		int delay = 1;
		char key;
		delay *= CLOCKS_PER_SEC;

		clock_t now = clock();
		bool pressed = false;

		int randomInt = rand() % 4;

		system("cls");

		printArrow(randomInt);

		cout << "Attacking";
		while (clock() - now < delay) {

			if (_kbhit()) {
				key = _getch();
				pressed = true;
			}
		}

		if (pressed) {
			switch (key) {
			case 'H'://up
				if (randomInt == 0) {
					cout << "\nBlocked!";
					return 1;
				}
				break;
			case 'P'://down
				if (randomInt == 1) {
					cout << "\nBlocked!";
					return 1;
				}
				break;
			case 'M'://right
				if (randomInt == 2) {
					cout << "\nBlocked!";
					return 1;
				}
				break;
			case 'K'://left
				if (randomInt == 3) {
					cout << "\nBlocked!";
					return 1;
				}
				break;
			default:
				cout << "\nMissed!" << key;
				break;
			}
			
		}
		else {
			cout << "\nnot pressed in time";
			return 0;
		}
	}

private:
	int enemySize;
	Fighter* playerPointer;
	Fighter *enemyPointer;
};







int main() {
	Player playerChar;
	wolf wolfEne1;
	wolf wolfEne2;
	skeleton skeletonEne1;

	Fighter tempArray[] = {wolfEne1, wolfEne2, skeletonEne1};
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
}
