#include <iostream>//cout cin
#include <conio.h>
#include <fstream>//file input and output
#include <string>//allows us to use strings
#include "Characters.cpp"
#include "Fight.cpp"

using namespace std;//so we can use cout and cin easier

const int arraySize = 20;//set the global size of our map array


class Save {//save state class - Stores, Alters, and Rewrites save data from our Save.txt file...
	//current state of the game is stored in this object, and then writted to the save file on closure of the app or reaching of a savestate
public:

	//constructor using data from save file  (Save.txt)
	Save(string nm, string st, int xp, int lvl, int hlth, int bBeaten, string powerupColl1, string powerupColl2) {
		stage = st;
		exp = xp;
		level = lvl;
		health = hlth;
		bossBeaten = bBeaten;
		name = nm;
		powerupCollection1 = powerupColl1;
		powerupCollection2 = powerupColl2;
	};


	void resetSave() {//reset our save (useful if save is corrupted)
		string contents = "Empty";//name 
		contents.append("\n0.txt");// stage
		contents.append("\n0");//xp
		contents.append("\n0");//lvl
		contents.append("\n100");//hlth
		contents.append("\n0");//bossBeaten?
		contents.append("\n0");//map3Powerup
		contents.append("\n0");//map7Powerup

		try {//try catch block
			ofstream saveTextFile("Save.txt");//open file to write

			if (!saveTextFile) {//if our file didnt open
				throw("File Open Error");//throw an error, exit run
			}

			saveTextFile << contents << endl;//write our save state "contents" variable into the file 
			saveTextFile.close();//close the file
		}
		catch (string e) {//catch error
			cout << e;//print the error
		}
	}

	void saveGame() {//puts our object data into a string to be written to our save file(Save.txt)
		resetSave();
		string contents = name;//name 
		contents.append("\n" + stage);// stage
		contents.append("\n" + to_string(exp));//xp
		contents.append("\n" + to_string(level));//lvl
		contents.append("\n" + to_string(health));//hlth
		contents.append("\n" + to_string(bossBeaten));//bossBeaten?
		contents.append("\n" + powerupCollection1);//map3Powerup
		contents.append("\n" + powerupCollection2);//map7Powerup

		try {//try catch block
			ofstream saveTextFile("Save.txt");//open file to write

			if (!saveTextFile) {//if our file didnt open
				throw("File Open Error");//throw an error, exit run
			}

			saveTextFile << contents << endl;//write our save state "contents" variable into the file 
			saveTextFile.close();//close the file
		}
		catch (string e) {//catch error
			cout << e;//print the error
		}
	}

public://variables that contain savestate data
	string stage;
	string name;
	string powerupCollection1;
	string powerupCollection2;
	int exp;
	int level;
	int health;
	int bossBeaten;
};

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
	//
	// 
	// 
	//function to open our map based on a string filename
	//function will read the map, copy the data into our mapArray[][] and set the perameters for this map's dimensions
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
			mapWidth = 0;
			mapHeight = 0;
			while (!myfile.eof())
			{
				getline(myfile, line);
				if (line.length() > mapWidth) {//if the current width is less than the length of our line, a longer line has been found, this increasing our upper bounds
					mapWidth = line.length();//set our mapWidth as this line's length
				}
				for (int x = 0; x < line.length(); x++) {
					mapArray[y][x] = line[x];
				}
				y++;
			}
			myfile.close();
			mapHeight = y;//each iteration marks the height of our map
		}
	}

	//function for interpretting the map data and printing out the correct/current gameview
	void printMap() {
		system("cls");
		//headHeight();//this test method would move our map down the screen
		for (int y = 0; y < arraySize; y++) { // iterate through our rows
			//giveSpace(); // this test method would move our map across the screen
			for (int x = 0; x < arraySize; x++) {//iterate through our columns
				if (playerPosX == x && playerPosY == y) {//if this position is our player location
					cout << "O";//print our player (O)
				}
				else {
					if (mapArray[y][x] == '#') {//prints walls
						cout << '#';
					}
					else if (mapArray[y][x] == 'p' || mapArray[y][x] == 'b') {// prints special items
						if (currentRoom == "3.txt" and savePointer->powerupCollection1 == "0") {//if we are in the correct room(3), AND this rooms powerup (powerupCollection1) has not been consumed (checking from our save state)
							cout << mapArray[y][x];//print the powerup
						}
						else if (currentRoom == "7.txt" and savePointer->powerupCollection2 == "0") {//if we are in the correct room (7), AND this rooms powerup(powerupCollection2) has not been consumed (checking from our save state)
							cout << mapArray[y][x];//print the powerup
						}
						else {//if the powerup has been consued
							cout << " ";//print out a blank space
							
							//this block of code means when we consume a powerup it isnt deleted from the map but simple hidden,
							// this means we dont have to constantly rewrite map data, saving potential file corruption/rewriting errors 
						}

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

	//function to move player into a spot on a new map, depending on what side of the screen the exited from
	void newScreen(string map) {
		int checkUp = 0;//0 - none, 1 - up, 2 - down
		int checkSide = 0; // 0 - none, 1 - right, 2 - left

		if (playerPosX < 1) {//if left
			checkSide = 1;//side = left
		}
		else if (playerPosX >= mapWidth - 1) {//if right
			checkSide = 2;
		}

		if (playerPosY < 1) {//if up
			checkUp = 1;
		}
		else if (playerPosY >= mapHeight - 1) {//if down
			checkUp = 2;
		}

		loadMap(map);//load our map

		if (checkUp != 0) {//if we must check vertical movement
			switch (checkUp) {
			case 1://up
				playerPosY = mapHeight - 2;//set height to button of screen
				break;
			case 2://down
				playerPosY = 1;//set height to top
				break;
			}
		}

		if (checkSide != 0) {//if we must check horizontal movement
			switch (checkSide) {
			case 1://left
				playerPosX = mapWidth - 2;//move to right of screen
				break;
			case 2://right
				playerPosX = 1;//move to left of screen
				break;
			}
		}

		currentRoom = map;//set our current room as the loaded map (local object variable)
		savePointer->stage = map;//update our map in our savestate
	}

	void update() {

		switch (currKey) {
		case up:
			if (!((playerPosY - 1) <= -1)) {//check our player is within the bounds
				if (!(mapArray[playerPosY - 1][playerPosX] == '#')) {//check if our player is moving onto a wall tile
					//if moving into a wall, then dont move, else
					playerPosY += -1;//move player
				}
				//following code allows us to toggle our on grass state to prevent repitition and overload
				if (!(mapArray[playerPosY][playerPosX] == '^')) {//if player has moved, and stepped onto grass,
					steppedOnGrass = true;// stepped onto grass == true
				}
			}
			break;
		case down:
			if (!((playerPosY + 1) >= arraySize)) {
				if (!(mapArray[playerPosY + 1][playerPosX] == '#')) {
					playerPosY += 1;
				}
				if (!(mapArray[playerPosY][playerPosX] == '^')) {
					steppedOnGrass = true;
				}
			}
			break;
		case left:
			if (!((playerPosX - 1) <= -1)) {
				if (!(mapArray[playerPosY][playerPosX - 1] == '#')) {
					playerPosX += -1;
				}
				if (!(mapArray[playerPosY][playerPosX] == '^')) {
					steppedOnGrass = true;
				}
			}
			break;
		case right:
			if (!((playerPosX + 1) >= arraySize)) {
				if (!(mapArray[playerPosY][playerPosX + 1] == '#')) {
					playerPosX += 1;
				}
				if (!(mapArray[playerPosY][playerPosX] == '^')) {
					steppedOnGrass = true;
				}
			}
			break;
		}

		currKey = none;//once movement has been carried out, reset movement

		char tile = mapArray[playerPosY][playerPosX];//get current tile...

		switch (tile) {//check current tile
		case 'p'://On a power up space
			if (currentRoom == "3.txt" and savePointer->powerupCollection1=="0") { // if in room 3 and the room 3 collectable hasnt been picked up:
				playerPointer->gainExp(2000);//add 2000exp
				savePointer->powerupCollection1 = "1";//set the powerup to collected
			}
			if (currentRoom == "7.txt" and savePointer->powerupCollection2=="0") {// if in room 7 and the room 7 collectable hasnt been picked up:
				playerPointer->gainExp(2000);//add 2000exp
				savePointer->powerupCollection2 = "1";//set the powerup to collected
			}//else do nothing because the Powerup is collected and now invisible
			break;
		case '^'://Tall Grass
			if (steppedOnGrass) {
				if ((rand() % 100 + 1) < 30) {//3 in 10 chance of encountering enemies

					Fighter** Enemies = new Fighter * [4];//create dynamically allocated pointer array on stack
					int arraySize = 1;

					//1 in 2 chance,
					if ((rand() % 2 + 1) == 1) {// if 1
						Enemies[0] = new skeleton;//append skeleton
					}
					else {//if 2
						Enemies[0] = new wolf;//append wolf
					}


					for (int i = 1; i < (rand() % 3 + 1); i++) {//create random number between 1,2,3 , starting at 1(because our Enemies[0] is already defined) ---> if 1, do nothing. if 2, add an extra enemy, if 3, add 2 extra enemies 
						//this section could change to (i = 0; (rand() % 2)) then set Enemies[i] to Enemies[i+1] to clear up a bit of confusion for the loop

						if ((rand() % 2 + 1) == 1) {//same as above(first item in enemy list), if 1 create skeleton, if 2 create wolf
							Enemies[i] = new skeleton;
						}
						else {
							Enemies[i] = new wolf;
						}
						arraySize++;//increase the array size each iteration
					}
					try {//try
						Fight newFight(playerPointer, *Enemies, arraySize);//create a new fight object with our player, enemies, and array size
					}
					catch (string e) {//catch a string throw (expected)
						cout << "Error occured: " << e << endl;
					}
					catch (exception e) {// catch an exception throw (unexpected)
						cout << "Unexpected Error Occured";
					}


					//delete pointer array
					for (int i = 0; i < arraySize; i++) {//Destroy Items
						delete Enemies[i];
					}
					delete[] Enemies;//Destroy Array
				}
				steppedOnGrass = false;//as we have ran stepped on grass, set state to false so it wont run again until another movement has been made
			}
			break;
			//Test if player is stepped on a level trigger, and trigger the according map
			//could be replaced newScreen(to_string(tile)) + ".txt" so -> tile = '0', to_string(tile) + ".txt" == "0.txt", however doesnt account for our maps greater than 9 as we cant fit two characters onto one space...
			//...thus having to use the switch case to assign unique characters (outside of the numerics) to a numbered map.
		case '0':// case (whatever the map tile is)
			newScreen("0.txt");//open up the corresponding map
			break;
		case '1':
			newScreen("1.txt");
			break;
		case '2':
			newScreen("2.txt");
			break;
		case '3':
			newScreen("3.txt");
			break;
		case '4':
			newScreen("4.txt");
			break;
		case '5':
			newScreen("5.txt");
			break;
		case '6':
			newScreen("6.txt");
			break;
		case '7':
			newScreen("7.txt");
			break;
		case '8':
			newScreen("8.txt");
			break;
		case '9':
			newScreen("9.txt");
			break;
		case 'v'://case v (as 10 cannot fit in a single character)
			newScreen("10.txt");//open map ten
			break;
		}
	}

	void getInput() {//function to get and process inputs
		if (_kbhit) {//if our keyboard is hit
			char keyPress = _getch();//our keypress is a char
			switch (keyPress) {//switch keypress condition (char)
			//game uses WASD movement so we take the according movement and translate it to a direction on our enum
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
			case 'c'://close game button (later likely replaced by a menu option)
				//closing the game
				savePointer->saveGame();//save current state
				GameOver = true;//set gameover to true to end gameLoop in main
				break;
			}
		}

	}

	void setSavePointer(Save* savePoint) {//public function called by save state to have it recognised in our game engine
		savePointer = savePoint;// set a pointer to save memory instead of calling entire object
	}

	void setPlayerPointer(Player* plyr) {//public function called by player to have it recognised in our game engine
		playerPointer = plyr;//set a pointer to save memory instead of calling entire object
	}

public://public variables

	int playerPosX = 5;//player pos (needed for map and save)
	int playerPosY = 5;//player pos (needed for map and save)

	bool GameOver = false; //game loop variable (defined here so we can break the loop from inside the class)

	string currentRoom = "0.txt";//default stage file (rewritten by save engine)
private:
	

	Save* savePointer;//pointer to our save engine object
	Player* playerPointer;//pointer to our player object

	char mapArray[arraySize + 10][arraySize + 10];//2d array storing our read map from txt
	int mapWidth;//width of array contents
	int mapHeight;//height of array contents

	bool steppedOnGrass = false;//variable to see if we've stepped onto a new set of grass (to stop our movement chance to encounter occuring rapidly, as tall grass should only have chance encounter when moving on it)

	enum key {//enum for our movement
		none = 0,
		up = 1,
		left = 2,
		down = 3,
		right = 4,
		esc = 5
	};

	key currKey = none;//for getting our current movement, set to none by default
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



int main() {//main program
	bool saveLoaded = false;// set save laoded to false
	string saveData[8];//made a string array for our save data

	//load save data
	try {
		string line;//string for line
		
		ifstream myfile("Save.txt");//open save file for reading

		int i = 0;//set iteration to 0
		while (!myfile.eof())//while we are not at the end of the file
		{
			getline(myfile, line);//get current line and set line variable as it
			if (line != "") {//if the line isnt blank
				saveData[i] = line;//make our savedata current iteration the line
			}
			i++;//increment i
		}
		myfile.close();//done reading file, time to close
		
		saveLoaded = true;//our save has been loaded
	}
	catch (string e) {//if we catch an error
		saveLoaded = false;//our save has not been loaded (corrupted or missing)
		//if error occurs
		Save Savestate("Empty", "0.txt", 0, 0, 100, 0, "0", "0");//mock up a default saveState
		Savestate.resetSave();//reset our save and write a new save file

		cout << "Error " << e;//return our error
		return -1;//end program with error code, but having reset the save file(should now read as intended)
	}
	catch(exception e){
		saveLoaded = false;

		Save Savestate("Empty", "0.txt", 0, 0, 100, 0, "0", "0");//mock up a default saveState
		Savestate.resetSave();//reset our save and rewrite a new save file (overwrites corrupted save, remakes a deleted/missing save

		cout << "Unexpected Error";
		return -1;//end program with error code, but having reset the save file(should now read as intended)
	}

	if (saveLoaded == false) {//if our save is not loaded
		Player PlayerMan(30, 30, 100, "Human", "You", 0, 0);//set the player to default
		Save Savestate("Empty", "0.txt", 0, 0, 100, 0, "0", "0");//set our save to default settings
		game gameEngine;//create a new game engine
	}

	Save Savestate(saveData[0], saveData[1], stoi(saveData[2]), stoi(saveData[3]), stoi(saveData[4]), stoi(saveData[5]), saveData[6], saveData[7]);//create save data object with our save file data

	Player PlayerMan(30, 30, Savestate.health, "Human", Savestate.name, Savestate.exp, Savestate.level);//create player object with Savestate object data
	game gameEngine;//create game engine
	//set our object pointers (variables in gameEngine class) using methods
	gameEngine.setPlayerPointer(&PlayerMan);
	gameEngine.setSavePointer(&Savestate);

	//set gameengine stage using savedata
	gameEngine.currentRoom = Savestate.stage;
	gameEngine.loadMap(Savestate.stage);

	//print stage
	gameEngine.printMap();

	while (gameEngine.GameOver == false) {//main game loop
		gameEngine.getInput();//Check for user input
		gameEngine.update();//update the game
		gameEngine.printMap();//print gamestate to screen
	}

	return 0;//end program
}
