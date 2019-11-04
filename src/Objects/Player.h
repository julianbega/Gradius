#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "Bullets.h"
#include "Bomb.h"

namespace gamesystem {
	using namespace bullets;
	using namespace bombs;
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
		void shootBullet(Bullets &bullet, Player player);
		void shootBomb(Bombs &bomb, Player player);
		void drawPlayer(Player player);
		void drawPlayerAnim(Player player, Texture2D frame1, Texture2D frame2);
		void drawPlayerLives(Player player);
		void movePlayer(Player &player);
	}
}
#endif PLAYER_H