#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace players {
	struct Player {
		Rectangle Body;
		Color Color;
		int Health;
		int Speed;
	};
	extern Player player;
	extern const int playerHealth;
	void init();
}
#endif PLAYER_H