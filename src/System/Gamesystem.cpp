#include "System/Gamesystem.h"
#include "Objects/Window.h"
#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/GroundFighter.h"
#include "Objects/Bullets.h"
#include "Objects/GroundFighterBullet.h"
#include "Objects/Bomb.h"
#include "Scenes/Menu.h"
#include "Scenes/Gameplay.h"
#include "Scenes/Credits.h"
#include "System/Sounds.h"
#include "raylib.h"
namespace gamesystem {
	bool gameIsOn = true;
	Gamestates Gamestate = Menu;
	void init();
	void runGame() {
		gamesystem::init();
		while (!WindowShouldClose() && gameIsOn) {
			updateMusic();
			switch (Gamestate) {
			case Menu:
				menu::run();
				break;
			case Game:
				gameplay::run();
				break;
			case Controls:
				break;
			case Credits:
				credits::run();
				break;
			case End:
				break;
			}
		}
		UnloadTexture(gameplay::frame1);
		UnloadTexture(gameplay::frame2);
	}
	void init() {
		window::init();
		menu::init();
		players::init();
		fighters::init();
		groundFighters::init();
		credits::init();
		gameplay::init();
		bullets::init();
		groundFighterBullets::init();
		bombs::init();
		InitAudioDevice();
		initializeMusic();
	}
}