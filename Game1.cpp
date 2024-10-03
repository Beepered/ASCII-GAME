#include "GameBasics.h"

namespace Game1 {
	int xPos = 0, yPos = 0;
	int mapLength = 6, mapHeight = 6;

	struct Item {
		int x, y;
	};

	std::vector<Item> itemList{};

	void AddItem(int x, int y) {
		if (x > mapLength - 1) {
			x = mapLength - 1;
		}
		if (y > mapHeight - 1) {
			y = mapHeight - 1;
		}
		struct Item newItem = { x, y };
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
		char key = _getch();
		switch (_getch()) {
		case KEY_UP:
			if (yPos != 0)
				yPos--;
			break;
		case KEY_DOWN:
			if (yPos != mapHeight - 1)
				yPos++;
			break;
		case KEY_LEFT:
			if (xPos != 0)
				xPos--;
			break;
		case KEY_RIGHT:
			if (xPos != mapLength - 1)
				xPos++;
			break;
		default:
			std::cout << "\n\nEXITED GAME\n";
			return 0;
			break;
		}
		return 1;
	}

	void DisplayMap() {
		std::vector<std::vector<char>> letters(mapHeight, std::vector<char>(mapLength, 0)); // using vector for changable height and length

		int itemToDelete = 0; // creating items
		for (Item item : itemList) {
			letters[item.y][item.x] = '#';
			if (xPos == item.x && yPos == item.y) { //check if player is on top of item
				std::cout << "ON TOP OF Item\n";
				itemList.erase(itemList.begin() + itemToDelete);
				itemToDelete++;
				;
			}
		}

		// creating enemy
		for (Enemy enemy : enemyList) {
			letters[enemy.y][enemy.x] = '!';
			if (xPos == enemy.x && yPos == enemy.y) { //check if player is on top of item
				std::cout << "ON TOP OF Enemy\n";
			}
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
void LoadGame1() {
	system("cls");
	Game1::AddItem(2, 80);
	Game1::AddItem(4, 2);
	Game1::AddEnemy(5, 3);
	Game1::DisplayMap();
	while (Game1::InputThing()) {
		system("cls");
		Game1::DisplayMap();
	}
}
