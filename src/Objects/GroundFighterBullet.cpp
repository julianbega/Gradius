#include "Objects/GroundFighterBullet.h"
#include "raylib.h"
#include "Objects/Window.h"

namespace gamesystem {
	using namespace window;
	namespace groundFighterBullets {
		const int groundFighterbulletWidth = 33;
		const int groundFighterbulletHeight = 15;
		const int groundFighterbulletSpeed = screenWidth / 2;
		Color groundFighterBulletColor = GREEN;
		GroundFighterBullets groundFighterBullet;
		void initGroundFighterBullets(GroundFighterBullets &groundFighterbulletSpeed, int width, int height, int speed, Color color);

		void init() {
			initGroundFighterBullets(groundFighterBullet, groundFighterbulletWidth, groundFighterbulletHeight, groundFighterbulletSpeed, groundFighterBulletColor);
		}
		void initGroundFighterBullets(GroundFighterBullets &groundFighterbullet, int width, int height, int speed, Color color) {
			groundFighterbullet.Body.height = height;
			groundFighterbullet.Body.width = width;
			groundFighterbullet.Color = color;
			groundFighterbullet.Speed = speed;
			groundFighterbullet.Active = false;
		}

	}
}