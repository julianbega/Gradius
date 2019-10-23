#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H
namespace gamesystem {
	enum Gamestates {
		Menu,
		Game,
		Controls,
		Credits,
		End
	};
	extern bool gameIsOn;
	extern Gamestates Gamestate;
	void runGame();
}
#endif GAMESYSTEM_H