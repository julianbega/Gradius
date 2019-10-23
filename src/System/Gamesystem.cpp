#include "System/Gamesystem.h"
#include "Objects/Window.h"
#include "Scenes/Menu.h"
#include "raylib.h"
namespace gamesystem {
	bool gameIsOn = true;
	Gamestates Gamestate = Menu;
	void init();
	void runGame() {
		gamesystem::init();
		while (!WindowShouldClose() && gameIsOn) {
			switch (Gamestate) {
			case Menu:
				menu::run();
				break;
			case Game:

				break;
			case Controls:
				break;
			case Credits:
				break;
			case End:
				break;
			}
		}
	}
	void init() {
		window::init();
		menu::init();
	}
}