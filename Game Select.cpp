#include "GameBasics.h"

void LoadMenu()
{
	system("cls");
	std::cout << "UP = Game 1: The IDEA\n";
	std::cout << "DOWN = Game 2: SHIP FIXER\n";
	std::cout << "LEFT = Game 3: Collect Item idea\n";

	std::cout << "\n\nGame 1: The IDEA\n";
	std::cout << "An unfinished \"not sure what to do with this\" game\n";
	std::cout << "Could be easily tweaked as a Collect Item game or box moving game, but I did not want to do level design\n";
	std::cout << "My personal challenge was not using random number generator or doing something every X seconds\n\n";

	std::cout << "Game 2: SHIP FIXER\n";
	std::cout << "I wanted to build off of Game 1, but didn't want to get rid of any work.\n";
	std::cout << "I had an idea to collect resources to build a ship\n";
	std::cout << "I wanted a game with no violence, which is harder than I thought, because there has to be an end goal and conflict or it will just be Animal Crossing\n";
	std::cout << "There isn't actually a ship in the game because I couldn't figure out how to draw out a ship from left to right and have it fly away\n\n";

	std::cout << "Game 3: Collect Item idea\n";
	std::cout << "I didn't want to make another big game like Game 2 so I just made a little project to build off of Game 1\n";
	std::cout << "This is a more fully realized idea of what a Game 1 game would be like, though it is more of a show-off\n\n";
	bool valid = false;
	while (!valid) {
		switch (char key = _getch()) {
		case KEY_UP:
			LoadGame1(); valid = true;
			break;
		case KEY_DOWN:
			LoadGame2(); valid = true;
			break;
		case KEY_LEFT:
			LoadGame3(); valid = true;
			break;
		case KEY_RIGHT:
			//std::cout << "Game 4\n";
			break;
		case ESCAPE:
			std::cout << "\n\nEXITED GAME\n"; valid = true;
			break;
		}
	}
}

int main() {
	LoadMenu();
}