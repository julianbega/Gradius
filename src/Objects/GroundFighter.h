#ifndef GROUNDFIGHTER_H
#define GROUNDFIGHTER_H
#include "raylib.h"
#include "GroundFighterBullet.h"
#include "Objects/Player.h"

namespace gamesystem {
	using namespace groundFighterBullets;
	using namespace players;
	namespace groundFighters {

		struct GroundFighter {
			Rectangle Body;
			Color Color;
			int Health;
			int Speed;
			bool Active;
		};
		extern GroundFighter groundFighter;
		extern const int groundFighterHealth;

		void init();
		void moveGroundFighter(GroundFighter &groundFighter);
		void moveGroundBullet(GroundFighterBullets &groundFighterBullet);
		void shootGroundBullet(GroundFighterBullets &groundFighterBullet, GroundFighter groundFighter);
		void drawGroundFighter(GroundFighter groundFighter);
		void drawGroundFighterBullet(GroundFighterBullets groundFighterBullet);
		void groundFighterShouldShoot(Player player);
	}
}
#endif