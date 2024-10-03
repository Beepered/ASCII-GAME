#include "GameBasics.h"

namespace Game3 {
	int xPos = 0, yPos = 0;
	int mapLength = 15, mapHeight = 8;
	int health = 3, coins = 0;

	struct Item {
		int x, y;
		char type;
	};

	std::vector<Item> itemList{};
	std::vector<char> playerItems{};

	void AddItem(int x, int y, char type) {
		if (x > mapLength - 1) {
			x = mapLength - 1;
		}
		if (y > mapHeight - 1) {
			y = mapHeight - 1;
		}
		struct Item newItem = { x, y, type };
		itemList.push_back(newItem);
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
		while (!valid) {
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
			case ESCAPE:
				std::cout << "\n\nEXITED GAME\n";
				valid = true;
				return 0;
				break;
			}
		}
		return 1;
	}

	void DisplayStats() {
		std::cout << "HEALTH: ";
		for (int i = 0; i < health * 5; i++) {
			std::cout << "|";
		}
		std::cout << "\nCoins: " << coins << "\n";
		std::cout << "Items: ";
		for (auto& item : playerItems) {
			std::cout << item << " ";
		}
		std::cout << "\n\n";
	}

	void GameLogic() {
		int itemToDelete = 0; // creating items
		for (Item item : itemList) {
			if (xPos == item.x && yPos == item.y) { //check if player is on top of item
				std::cout << "On top of item\n";
				if (item.type == 'O')
					coins++;
				else
					playerItems.push_back(item.type);
				itemList.erase(itemList.begin() + itemToDelete);
			}
			itemToDelete++;
		}

		// creating enemy
		int enemyToDestroy = 0;
		for (Enemy enemy : enemyList) {
			if (xPos == enemy.x && yPos == enemy.y) { //check if player is on top of item
				health--;
				enemyList.erase(enemyList.begin() + enemyToDestroy);
			}
			enemyToDestroy++;
		}
	}

	void DisplayMap() {
		std::vector<std::vector<char>> letters(mapHeight, std::vector<char>(mapLength, 0)); // using vector for changable height and length

		for (Item item : itemList) {
			letters[item.y][item.x] = item.type;
		}

		int enemyToDestroy = 0;
		for (Enemy enemy : enemyList) {
			letters[enemy.y][enemy.x] = 'X';
		}

		letters[yPos][xPos] = 'a';
		for (auto& y : letters) {
			for (auto& x : y) {
				if (x == '\0') {
					std::cout << "[ ]";
				}
				else {
					std::cout << "[" << x << "]";
				}
			}
			std::cout << "\n";
		}
	}
}
void LoadGame3() {
	system("cls");
	Game3::AddItem(2, 13, 'O'); Game3::AddItem(4, 2, 'O');
	Game3::AddItem(6, 10, 'O'); Game3::AddItem(7, 3, 'O');
	Game3::AddItem(12, 12, 'O'); Game3::AddItem(12, 15, 'O');
	Game3::AddItem(13, 1, 'O'); Game3::AddItem(15, 15, 'O');
	Game3::AddItem(5, 5, 'Y');
	Game3::AddItem(9, 0, '3');
	Game3::AddEnemy(0, 2);
	Game3::AddEnemy(5, 3);
	Game3::AddEnemy(3, 0);
	Game3::AddEnemy(2, 6);
	Game3::AddEnemy(9, 4);
	Game3::AddEnemy(9, 7);
	Game3::AddEnemy(13, 7);
	Game3::AddEnemy(15, 1);

	Game3::DisplayStats();
	Game3::DisplayMap();
	while (Game3::InputThing()) {
		system("cls");
		Game3::GameLogic();
		Game3::DisplayStats();
		Game3::DisplayMap();
		if (Game3::health == 0) {
			std::cout << "\nDEAD\n";
			break;
		}
		else if (Game3::coins > 3) {
			std::cout << "\nWIN\n";
			break;
		}
	}
}
