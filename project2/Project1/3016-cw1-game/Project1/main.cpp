#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

const int arraySize = 10;

class game {
public:

	//development test to put the map in the middle of the screen, scrapped because adding extra cout commands caused heavy flicker for the display
	void headHeight() {
		for (int i = 0; i < 10; i++) {
			cout << endl;
		}
	}

	void giveSpace() {
		for (int i = 0; i < 20; i++) {
			cout << " ";
		}
	}

	void loadMap(string levelName) {
		string line;
		ifstream myfile(levelName);

		for (int y = 0; y < arraySize; y++) {
			for (int x = 0; x < arraySize; x++) {
				mapArray[y][x] = ' ';
			}
		}

		if (myfile.is_open())
		{
			int y = 0;
			while (!myfile.eof())
			{
				getline(myfile, line);
				for (int x = 0; x < line.length(); x++) {
					mapArray[y][x] = line[x];
				}
				y++;
			}
			myfile.close();
		}
		else cout << "Unable to open file";
	}

	void printMap() {
		system("cls");
		//headHeight();
		for (int y = 0; y < arraySize; y++) {
			//giveSpace();
			for (int x = 0; x < arraySize; x++) {
				if (playerPosX == x && playerPosY == y) {
					cout << "O";
				}
				else {
					if (mapArray[y][x] == '#') {//prints walls
						cout << '#';
					}
					else if(mapArray[y][x] == 'p' || mapArray[y][x] == 'b'){// prints special items
						cout << mapArray[y][x];
						
					}
					else {//prints blank space
						cout << ' ';
					}
					//cout << mapArray[y][x];
				}
			}
			cout << endl;
		}
		char tile = mapArray[playerPosY][playerPosX];
		cout << tile;
	}

	void newScreen(string map, int posY, int posX) {
		loadMap(map);
		playerPosX = posX;
		playerPosY = posY;
		currentRoom = map;
	}

	void update() {

		switch (currKey) {
		case up:
			if (!((playerPosY - 1) <= -1)) {
				if (!(mapArray[playerPosY-1][playerPosX] == '#')) {
					playerPosY += -1;
				}
			}
			break;
		case down:
			if (!((playerPosY + 1) >= arraySize)) {
				if (!(mapArray[playerPosY+1][playerPosX] == '#')) {
					playerPosY += 1;
				}
			}
			break;
		case left:
			if (!((playerPosX - 1) <= -1)){
				if (!(mapArray[playerPosY][playerPosX-1] == '#')) {
					playerPosX += -1;
				}
			}
			break;
		case right:
			if (!((playerPosX + 1) >= arraySize)) {
				if (!(mapArray[playerPosY][playerPosX+1] == '#')) {
					playerPosX += 1;
				}
			}
			break;
		}

		currKey = none;

		char tile = mapArray[playerPosY][playerPosX];

		switch (tile) {
		    case '0':
			newScreen("0.txt", 1, 5);
			break;
			case '1':
				if (currentRoom == "0.txt") {
					newScreen("1.txt", 7, 5);
				}
				if (currentRoom == "2.txt") {
					newScreen("1.txt", 1, 5);
				}
			
			break;
			case '2':
				if (currentRoom == "3.txt") {
					newScreen("2.txt", 4, 8);
				}
				if (currentRoom == "1.txt") {
					newScreen("2.txt", 7, 5);
				}
			
			break;
			case '3':
			newScreen("3.txt", 4, 1);
			break;
			case '4':
			newScreen("4.txt", 7, 5);
			break;
			case '5':
			newScreen("5.txt", 7, 5);
			break;
			case '6':
			newScreen("6.txt", 1, 5);
			break;
			case '7':
			newScreen("7.txt", 7, 5);
			break;
			case '8':
			newScreen("8.txt", 7, 5);
			break;
			case '9':
			newScreen("9.txt", 7, 5);
			break;
		}
	}

	void getInput() {
		if (_kbhit) {
			char keyPress = _getch();
			switch (keyPress) {
				case 'w':
					currKey = up;
					break;
				case 'a':
					currKey = left;
					break;
				case 's':
					currKey = down;
					break;
				case 'd':
					currKey = right;
					break;
				case 'c':
					
					break;
				}
		}
		
	}

public:

	int playerPosX = 5;
	int playerPosY = 5;

private:
	string currentRoom = "0.txt";

	char mapArray[arraySize+10][arraySize+10];

	enum key {
		none = 0,
		up = 1,
		left = 2,
		down = 3,
		right = 4,
		esc = 5
	};

	key currKey = none;
};

//class level {
//public:
//	level(string levelName) {//level constructor reads the given txt file name into array "mapArray" which is currently only 10 lines long (could be peramater for 
//		string line;
//		ifstream myfile(levelName);
//		if (myfile.is_open())
//		{
//			int y = 0;
//			while (!myfile.eof())
//			{
//				getline(myfile, line);
//				mapArray[y] = line;
//				y++;
//			}
//			myfile.close();
//		}
//		else cout << "Unable to open file";
//	}
//
//	void printMap() {
//		for (int y = 0; y < arraySize; y++) {
//			for (int x = 0; x < arraySize; x++) {
//				
//			}
//		}
//	}
//
//private:
//	string mapArray[10];
//};



int main() {
	game gameEngine;
	gameEngine.loadMap("0.txt");
	gameEngine.printMap();

	while (true) {
		gameEngine.getInput();
		gameEngine.update();
		gameEngine.printMap();
	}

	return 0;
}