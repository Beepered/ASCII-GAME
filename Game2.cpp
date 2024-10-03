#include "GameBasics.h"

namespace Game2 {
	int xPos = 5, yPos = 5;
	int mapLength = 11, mapHeight = 11;
	int wood = 9990, rock = 9990;
	int woodLevel = 1, rockLevel = 1, shipLevel = 0;

	int turns = 0, totalTurns = 0, enemySpawn = 110, enemySpawnPos = 0; // enemySpawnPos is where to spawn enemy

	int woodNeeded = 5, rockNeeded = 0; // ship upgrade
	int woodUpgradeNeeded = 25, rockUpgradeNeeded = 25; // tool upgrades
	int wallWood = 0, wallRock = 0; // wall upgrades
	char objOnTopOf;

	bool win = false;

	struct Object {
		int x, y;
		char type; // tree, rock, upgrade1, upgrade2, ship, walls
	};

	std::vector<Object> objList{};

	void AddObject(int x, int y, char type) {
		if (x > mapLength - 1) {
			x = mapLength - 1;
		}
		if (y > mapHeight - 1) {
			y = mapHeight - 1;
		}
		struct Object newObj = { x, y, type };
		objList.push_back(newObj);
	}

	struct Enemy {
		int x, y;
	};

	std::vector<Enemy> enemyList{};
	void AddEnemy(int x, int y) {
		if (x > mapLength - 1) {
			x = mapLength - 1;
		}
		if (y > mapHeight - 1) {
			y = mapHeight - 1;
		}
		struct Enemy newEnemy = { x, y };
		enemyList.push_back(newEnemy);
	}

	int InputThing() {
		bool valid = false;
		while (!valid) { // only accept valid inputs
			switch (char key = _getch()) {
			case KEY_UP:
				if (yPos != 0) {
					yPos--;
					valid = true;
				}
				break;
			case KEY_DOWN:
				if (yPos != mapHeight - 1) {
					yPos++;
					valid = true;
				}
				break;
			case KEY_LEFT:
				if (xPos != 0) {
					xPos--;
					valid = true;
				}
				break;
			case KEY_RIGHT:
				if (xPos != mapLength - 1) {
					xPos++;
					valid = true;
				}
				break;
			case SPACE:
				switch (objOnTopOf) {
				case 'Y':
					wood += woodLevel;
					valid = true;
					break;
				case '0':
					rock += rockLevel;
					valid = true;
					break;
				case 'A':
					if (rock >= rockUpgradeNeeded) {
						woodLevel++;
						rock -= rockUpgradeNeeded;
						rockUpgradeNeeded += 35;
						valid = true;
					}
					break;
				case 'B':
					if (wood >= woodUpgradeNeeded) {
						rockLevel++;
						wood -= woodUpgradeNeeded;
						woodUpgradeNeeded += 35;
						valid = true;
					}
					break;
				case 'H':
					if (wood >= wallWood && rock >= wallRock) {
						wood -= wallWood; rock -= wallRock;
						wallWood = 0; wallRock = 0;
						valid = true;
					}
					break;
				case '8':
					if (wood >= woodNeeded && rock >= rockNeeded) {
						shipLevel++;
						wood -= woodNeeded; rock -= rockNeeded;
						switch (shipLevel) {
						case 1: // add rock
							AddObject(9, 2, '0');
							woodNeeded = 20; rockNeeded = 15;
							break;
						case 2: // add walls
							AddObject(4, 4, 'H'); AddObject(5, 4, 'H'); AddObject(6, 4, 'H');
							AddObject(4, 5, 'H'); AddObject(6, 5, 'H');
							AddObject(4, 6, 'H'); AddObject(5, 6, 'H'); AddObject(6, 6, 'H');
							woodNeeded = 30; rockNeeded = 30;
							break;
						case 3: // add upgrade 1, 2
							AddObject(3, 9, 'A');
							AddObject(7, 9, 'B');
							woodNeeded = 40; rockNeeded = 40;
							enemySpawn -= 10;
							break;
						case 4:
							woodNeeded = 60; rockNeeded = 60;
							break;
						case 5:
							woodNeeded = 80; rockNeeded = 80;
							enemySpawn -= 5;
							break;
						case 6:
							woodNeeded = 130; rockNeeded = 130;
							enemySpawn -= 10;
							break;
						case 7:
							woodNeeded = 250; rockNeeded = 250;
							enemySpawn -= 5;
							break;
						case 8:
							win = true;
							return 0;
							break;
						}
						valid = true;
					}
					break;
				}
				break;
			case ESCAPE:
				std::cout << "\n\nEXITED GAME\n";
				valid = true;
				return 0;
				break;
			}
		}
		turns++; totalTurns++;
		if (totalTurns == 130 && shipLevel < 3) {
			enemySpawn = 100;
		}
		else if (totalTurns == 170 && shipLevel < 3) {
			enemySpawn = 90;
		}
		if (totalTurns > 40 && totalTurns % 60 == 0) {
			enemySpawn--;
		}
	}

	void EnemySpawn() { // spawning enemies and enemy behavior
		int enemyToDestroy = 0;
		for (auto& enemy : enemyList) {
			if (xPos > enemy.x) {
				enemy.x++;
			}
			else if (xPos < enemy.x) {
				enemy.x--;
			}
			else if (yPos > enemy.y) {
				enemy.y++;
			}
			else if (yPos < enemy.y) {
				enemy.y--;
			}
			if ((enemy.x >= 4 && enemy.x <= 6) && (enemy.y >= 4 && enemy.y <= 6) && shipLevel >= 2 && wallWood < 50 && wallRock < 50) {  // IF ENEMY IS AT WALL
				wallWood += 10; wallRock += 10;
				enemyList.erase(enemyList.begin() + enemyToDestroy);
			}
			else if (xPos == enemy.x && yPos == enemy.y) { // if player on top of enemy
				enemyList.erase(enemyList.begin() + enemyToDestroy);
				wood -= 25; rock -= 25;
				if (wood < 0) {
					wood = 0;
				}
				if (rock < 0) {
					rock = 0;
				}
			}
			enemyToDestroy++;
		}

		if (turns >= enemySpawn) {
			turns = 0;
			enemySpawnPos++;
			switch (enemySpawnPos) {
			case 0:
				AddEnemy(0, 5);
				break;
			case 1:
				AddEnemy(5, 11);
				break;
			case 2:
				AddEnemy(11, 5);
				enemySpawnPos = 0;
				break;
			}
		}
	}

	void DisplayStats() {
		std::cout << "turns: " << totalTurns << "\n";
		for (int i = 0; i < shipLevel * 4; i++) { // ship percentage
			std::cout << "|";
		}
		std::cout << ((float)shipLevel / 8) * 100 << "%\n";

		for (int i = 0; i < 11; i++) {
			std::cout << " - ";
		}
		std::cout << "\n\tY: " << wood << "\t\t0: " << rock << "\n";
		std::cout << "\tY Lvl: " << woodLevel << "\t0 Lvl: " << rockLevel << "\n";
		for (int i = 0; i < 11; i++) {
			std::cout << " - ";
		}
		std::cout << "\n\n";
	}

	void DisplayMap() {
		std::vector<std::vector<char>> letters(mapHeight, std::vector<char>(mapLength, 0)); // using vector for changable height and length

		objOnTopOf = NULL;
		for (Object item : objList) {
			letters[item.y][item.x] = item.type;
			if (xPos == item.x && yPos == item.y) { //check if player is on top of object
				objOnTopOf = item.type;
				std::cout << "\t" << item.type << "\n";
				switch (item.type) {
				case 'A':
					std::cout << "\t0: " << rockUpgradeNeeded << "\n";
					break;
				case 'B':
					std::cout << "\tY: " << woodUpgradeNeeded << "\n";
					break;
				case 'H':
					std::cout << "\tY: " << wallWood << "\t0: " << wallRock << "\n";
					std::cout << "\t" << ((float)wallWood / 50) * 100 << "% destroyed\n";
					break;
				case '8':
					std::cout << "\tY: " << woodNeeded << "   0: " << rockNeeded << "\n";
					break;
				}
			}
		}

		for (auto& enemy : enemyList) {		// creating enemy
			letters[enemy.y][enemy.x] = 'X';
		}

		//display map and player
		letters[yPos][xPos] = 'a';
		for (auto& y : letters) {
			for (auto& x : y) {
				if (x == '\0') {
					std::cout << " - ";
				}
				else {
					std::cout << "[" << x << "]";
				}
			}
			std::cout << "\n";
		}
	}

	void DisplayEndGame() { // END GAME DISPLAY
		system("cls");
		std::cout << "\tGAME COMPLETE\n";
		std::cout << "\tTurns Taken: " << totalTurns << "\n\n";
		std::cout << "Press Escape to EXIT\tPress Space to go to Menu\n";
		EnemySpawn();
		DisplayStats();
		DisplayMap();
	}

	void ResetGame() {
		xPos = 5, yPos = 5;
		wood = 0, rock = 0;
		woodLevel = 1, rockLevel = 1, shipLevel = 0;

		turns = 0, totalTurns = 0, enemySpawn = 110, enemySpawnPos = 0;

		woodNeeded = 5, rockNeeded = 0; // ship upgrade
		woodUpgradeNeeded = 25, rockUpgradeNeeded = 25; // tool upgrades
		wallWood = 0, wallRock = 0; // wall upgrades
		objOnTopOf = NULL;

		objList.clear();

		win = false;
	}
}

void LoadGame2() {
	system("cls");
	Game2::ResetGame();
	Game2::AddObject(5, 0, '8');
	Game2::AddObject(1, 2, 'Y');

	Game2::DisplayStats();
	Game2::DisplayMap();
	while (Game2::InputThing()) {
		system("cls");
		Game2::EnemySpawn();
		Game2::DisplayStats();
		Game2::DisplayMap();
	}
	if (Game2::win) {
		Game2::DisplayEndGame();
		bool valid = false;
		while (!valid) {
			switch (char key = _getch()) {
			case SPACE:
				LoadMenu();
				valid = true;
				break;
			case ESCAPE:
				std::cout << "\n\nEXITED GAME\n";
				valid = true;
				break;
			}
		}
	}
}