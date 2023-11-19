#include <iostream>//cout cin
#include <conio.h>
#include <fstream>//file input and output
#include <string>//allows us to use strings
#include <ctime>//clock(),CLOCKS_PER_SEC

//include files
#include "Characters.cpp"


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
		name = "Empty";
		stage = "0.txt";
		exp = 0;
		level = 1;
		health = 100;
		bossBeaten = 0;
		powerupCollection1 = "0";
		powerupCollection2 = "0";

		string contents = "Empty";//name 
		contents.append("\n0.txt");// stage
		contents.append("\n0");//xp
		contents.append("\n1");//lvl
		contents.append("\n100");//hlth
		contents.append("\n0");//bossBeaten?
		contents.append("\n0");//map3Powerup
		contents.append("\n0");//map7Powerup

		try {//try catch block
			ofstream saveTextFile("Save.txt");//open file to write

			if (!saveTextFile) {//if our file didnt open
				throw string("File Open Error");//throw an error, exit run
			}

			saveTextFile << contents << endl;//write our save state "contents" variable into the file 
			saveTextFile.close();//close the file
		}
		catch (string e) {//catch error
			cout << e;//print the error
		}
	}

	void saveGame(Player* playerChar) {//puts our object data into a string to be written to our save file(Save.txt)
		exp = playerChar->getExp();
		health = playerChar->getMaxHealth();
		level = playerChar->getLevel();
		name = playerChar->getName();

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
				throw string("File Open Error");//throw an error, exit run
			}

			saveTextFile << contents << endl;//write our save state "contents" variable into the file 
			saveTextFile.close();//close the file
		}
		catch (string e) {//catch error
			cout << e;//print the error
			resetSave();
		}
	}
	//resetFromSave(string namSave, int healthSave, int experienceSave, int lvlSave) 
	string loadSave(Player* playerChar) {
		playerChar->resetFromSave(name, health, exp, level);
		return stage;
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
					else if (mapArray[y][x] == 'M') {//prints walls
						cout << 'M';
					}
					else if (mapArray[y][x] == 'H') {//prints walls
						cout << 'H';
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
		if (playerPointer->getHealth() <= 0) {//if a player has no health (death from combat)
			cout << "You Have Died..." << endl; //print death message
			cout << "Continuing from previous save, press enter to continue..";
			while (_getch() != '\r') {//wait for confirmation

			}
			playerDead = true;
		}

		switch (currKey) {//which direction is being pressed?
		case up:
			if (!((playerPosY - 1) <= -1)) {//check our player is within the bounds
				if (!(mapArray[playerPosY - 1][playerPosX] == '#')) {//check if our player is moving onto a wall tile
					//if moving into a wall, then dont move, else
					playerPosY += -1;//move player
				}
				//following code allows us to toggle our on grass state to prevent repitition and overload
				if (!(mapArray[playerPosY][playerPosX] == 'M')) {//if player has moved, and stepped onto grass,
					steppedOnGrass = true;// stepped onto grass == true
				}
			}
			break;
		case down:
			if (!((playerPosY + 1) >= arraySize)) {
				if (!(mapArray[playerPosY + 1][playerPosX] == '#')) {
					playerPosY += 1;
				}
				if ((mapArray[playerPosY][playerPosX] == 'M')) {
					steppedOnGrass = true;
				}
			}
			break;
		case left:
			if (!((playerPosX - 1) <= -1)) {
				if (!(mapArray[playerPosY][playerPosX - 1] == '#')) {
					playerPosX += -1;
				}
				if ((mapArray[playerPosY][playerPosX] == 'M')) {
					steppedOnGrass = true;
				}
			}
			break;
		case right:
			if (!((playerPosX + 1) >= arraySize)) {
				if (!(mapArray[playerPosY][playerPosX + 1] == '#')) {
					playerPosX += 1;
				}
				if ((mapArray[playerPosY][playerPosX] == 'M')) {
					steppedOnGrass = true;
				}
			}
			break;
		}

		currKey = none;//once movement has been carried out, reset movement

		char tile = mapArray[playerPosY][playerPosX];//get current tile...

		switch (tile) {//check current tile
		case 'p'://On a power up space
			if (currentRoom == "3.txt" and savePointer->powerupCollection1 == "0") { // if in room 3 and the room 3 collectable hasnt been picked up:
				playerPointer->gainExp(2000);//add 2000exp
				savePointer->level = playerPointer->getLevel();//save our level to the saveEngine
				savePointer->exp = playerPointer->getExp();//save our exp to the saveEngine
				savePointer->powerupCollection1 = "1";//set the powerup to collected
			}
			if (currentRoom == "7.txt" and savePointer->powerupCollection2 == "0") {// if in room 7 and the room 7 collectable hasnt been picked up:
				playerPointer->gainExp(2000);//add 2000exp
				savePointer->level = playerPointer->getLevel();//save our level to the saveEngine
				savePointer->exp = playerPointer->getExp();//save our exp to the saveEngine
				savePointer->powerupCollection2 = "1";//set the powerup to collected
			}//else do nothing because the Powerup is collected and now invisible
			break;
		case 'M'://Tall Grass
			tallGrass();//if on tall grass, call our tallgrass function
			break;
		case 'H':
			cout << "Full Health Recovered!" << endl << "Press any key to Continue...";
			playerPointer->heal();
			_getch();
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
		case 'a'://case a (as 10 cannot fit in a single character) START BOSS FIGHT IF THE BOSS HASNT BEEN BEATEN ALREADY

			if (savePointer->bossBeaten == 0) {//if the boss hasn't been beaten

				//start fight with the boss
				Fight newFight(playerPointer, new Demon, 1);
				newFight.startFight();
				newFight.Menu(0, 1);
				bool Menu = true;
				int menuNumTemp = 1;
				while (Menu) {
					getInput();
					system("cls");
					menuNumTemp = newFight.Menu((int)currKey, menuNumTemp);
					Menu = newFight.Status();
					currKey = none;
				}
				if (playerPointer->getHealth() > 0) {//if the fight is over and the player is alive
					savePointer->bossBeaten = 1;//the boss has been beaten
				}
			}
			else {
				newScreen("10.txt");//open map ten
			}
			break;

		case 'b': //Beat The Game (ending cutscene)
			system("cls");

			slowPrint("And the Hero Dissapears into the sunset...", 0.2f);
			cout << endl;
			slowPrint("Though his Acolayde was defeated...", 0.2f);
			slowPrint("The Demon King Still Lurks In the Crust of the earth...", 0.2f);
			cout << endl;
			slowPrint("To Be Continued...", 0.5f);
			GameOver = true;//set gameover to true to end gameLoop in main
			_getch();
			break;

		}
	}

	void slowPrint(string text, float delayInp) {//Gets a string and slowly prints it to the screen using the delay
		//Slow Print
		float delay = delayInp;//delay (in seconds) between our attacks
		char key;//our key pressed
		delay *= CLOCKS_PER_SEC;//convert our seconds delay into clocks
		for (int i = 0; i < text.length(); i++) {
			clock_t now = clock();//set a clock
			while (clock() - now < delay) {//while our delay isnt up
			}
			cout << text[i];
		}
		cout << endl;
	}

	void tallGrass() {
		if (steppedOnGrass) {//if we have stepped onto the grass (and aren't just on it during an update)
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(1, 100);
			if (dist(mt) <= 33) {//3 in 10 chance of encountering enemies
				try {//try
					if (dist(mt) <= 50) {// 50/50 chance to fight skeleton or wolf
						Fight newFight(playerPointer, (new skeleton), arraySize);//create a new fight object with our player, enemies, and array size
						newFight.startFight();//start the fight
						newFight.Menu(0, 1); // initialise our menu
						bool Menu = true;//menu loop condition
						int menuNumTemp = 1;//menu item selection 
						while (Menu) {//while we are in the menu
							getInput();//get input
							system("cls");//clear screen
							menuNumTemp = newFight.Menu((int)currKey, menuNumTemp);//send the pressed key to the menu method
							Menu = newFight.Status();//get the status of the fight 
							currKey = none;//reset current key
						}
					}
					else {//same as above
						Fight newFight(playerPointer, (new wolf), arraySize);//create a new fight object with our player, enemies, and array size
						newFight.startFight();
						newFight.Menu(0, 1);
						bool Menu = true;
						int menuNumTemp = 1;
						while (Menu) {
							getInput();
							system("cls");
							menuNumTemp = newFight.Menu((int)currKey, menuNumTemp);
							Menu = newFight.Status();
							currKey = none;
						}
					}
				}
				catch (string e) {//catch a string throw (expected)
					cout << "Error occured: " << e << endl;
				}
				catch (exception e) {// catch an exception throw (unexpected)
					cout << "Unexpected Error Occured";
				}
			}
			steppedOnGrass = false;//as we have ran stepped on grass, set state to false so it wont run again until another movement has been made
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
				savePointer->saveGame(playerPointer);//save current state
				GameOver = true;//set gameover to true to end gameLoop in main
				break;

			case '\r':
			case 'f':
			case 'e':
				currKey = select;
			}
		}

	}

	int returnInput() {
		return currKey;
	}

	void resetInput() {
		currKey = none;
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
	bool playerDead = false;

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
		esc = 5,
		select = 6
	};

	key currKey = none;//for getting our current movement, set to none by default
};


int main() {//main program
	bool saveLoaded = false;// set save laoded to false
	string saveData[8];//made a string array for our save data
	cout << "Starting" << endl;
	//load save data
	try {
		string line;//string for line

		ifstream myfile("Save.txt");//open save file for reading

		if (!myfile.is_open()) {
			throw string("File Found Error, Resolving (Please Restart Application)");
		}

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
		Save Savestate("Empty", "0.txt", 0, 0, 150, 0, "0", "0");//mock up a default saveState
		Savestate.resetSave();//reset our save and write a new save file

		cout << "Error " << e;//return our error
		return -1;//end program with error code, but having reset the save file(should now read as intended)
	}
	catch (exception e) {
		saveLoaded = false;

		Save Savestate("Empty", "0.txt", 0, 0, 150, 0, "0", "0");//mock up a default saveState
		Savestate.resetSave();//reset our save and rewrite a new save file (overwrites corrupted save, remakes a deleted/missing save

		cout << "Unexpected Error";
		return -1;//end program with error code, but having reset the save file(should now read as intended)
	}

	if (saveLoaded == false) {//if our save is not loaded
		Player PlayerMan(30, 30, 100, "Human", "You", 0, 0);//set the player to default
		Save Savestate("Empty", "0.txt", 0, 0, 150, 0, "0", "0");//set our save to default settings
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


	bool startMenuRun = true;//Condition to run menu
	int menuNum = 1;//menu location
	while (startMenuRun) {//while Running menu

		switch (gameEngine.returnInput()) {//switch keypress condition (char)
		case 1://up
			menuNum = menuNum - 1;//move cursor up
			if (menuNum < 1) {//if cursor is at continue, loop to quit
				menuNum = menuNum + 3;
			}
			
			break;
		case 3://down
			menuNum = menuNum + 1;//move cursor down
			if (menuNum > 3) {//if cursor is at quit, loop to continue
				menuNum = menuNum - 3;
			}
			break;

		case 6:
			switch (menuNum) {
			case 1://continue
				//set gameengine stage using savedata
				gameEngine.currentRoom = Savestate.stage;
				gameEngine.loadMap(Savestate.stage);

				startMenuRun = false;//exit while loop

				break;
			case 2://new game
				Savestate.resetSave();
				//set gameengine stage using savedata
				PlayerMan.updateSave(Savestate.name, Savestate.level, Savestate.exp, Savestate.health);
				gameEngine.currentRoom = Savestate.stage;
				gameEngine.loadMap(Savestate.stage);

				startMenuRun = false;//exit while loop

				break;
			case 3://Quit
				gameEngine.GameOver = true;//set gameover to true to skip gameloop

				startMenuRun = false;//exit while loop

				break;
			}
			break;
		}

		cout << "Welcome to the game.." << endl;
		switch (menuNum) {//update our onscreen menu to show
		case 1://Fight
			cout << endl << "Continue[@]" << endl << "New Game[ ]" << endl << "Quit[ ]" << endl;
			break;
		case 2://Fight
			cout << endl << "Continue[ ]" << endl << "New Game[@]" << endl << "Quit[ ]" << endl;
			break;
		case 3://Fight
			cout << endl << "Continue[ ]" << endl << "New Game[ ]" << endl << "Quit[@]" << endl;
			break;
		}

		if (startMenuRun) {
			gameEngine.resetInput();
			gameEngine.getInput();
		}

		system("cls");
	}

	if (gameEngine.GameOver != true) {//if the player didnt
		if (Savestate.name == "Empty") { //if the name has not been set yet
			PlayerMan.setName();//set name
			Savestate.saveGame(&PlayerMan);//save new name
			if (PlayerMan.getName() != "Dev") { // if the player name is Dev then skip this section
				//Introduction "Cutscene"
				system("cls");
				gameEngine.slowPrint("In a Shallow Valley Resting Between Two Great And Ancient Peaks...", 0.15f);
				cout << endl;
				gameEngine.slowPrint("A Retired Warrior Gazes At The Horizon...", 0.15f);
				cout << endl;
				gameEngine.slowPrint("........", 0.5f);
				cout << endl;
				gameEngine.slowPrint("When Suddenly...", 0.01f);
				gameEngine.slowPrint("A Great Fire Erupts Over the Mountain...A Demon Acolayde Rises From the Crust of the Earth!", 0.1f);
				cout << endl;
				gameEngine.slowPrint("Our Hero " + PlayerMan.getName() + ", Grabbing His Old Sword and Donning his Armour, Sets Off into the Dangerous Forest to Defeat the Beast..", 0.1f);
				gameEngine.slowPrint("Before its too late....", 0.2f);
				gameEngine.slowPrint("Press Any Key to Continue...", 0.2f);
				_getch();//pause for user to read text
			}
		}
	}

	//update and print the map before entering the loop so we can grab the input first
	string stageTemp = Savestate.loadSave(&(PlayerMan));
	gameEngine.update();//update the game
	gameEngine.printMap();//print gamestate to screen


	while (gameEngine.GameOver == false) {//main game loop
		gameEngine.getInput();//Check for user input
		gameEngine.update();//update the game
		gameEngine.printMap();//print gamestate to screen
		if (gameEngine.playerDead) {
			string stageTemp = Savestate.loadSave(&(PlayerMan));
			gameEngine.currentRoom = stageTemp;
			gameEngine.loadMap(stageTemp);
			gameEngine.playerDead = false;
		}
	}

	return 0;//end program
}
