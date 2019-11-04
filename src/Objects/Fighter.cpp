#include "Objects\Fighter.h"
#include "Objects\Window.h"

namespace gamesystem {
	using namespace window;
	namespace fighters {

		const Color fighterColor = RED;
		const int fighterWidth = 20;
		const int fighterHeight = 10;
		const int fighterX = GetRandomValue(screenWidth + fighterWidth, screenWidth + 2 * fighterWidth);
		const int fighterY = screenHeight/2;
		const int fighterSpeed = screenWidth / 2;
		const int fighterHealth = 1;
		Fighter fighter;

		void initFighter(Fighter &Fighter, int width, int height, int x, int y, int lives, int speed, Color color);

		void init() {
			initFighter(fighter, fighterWidth, fighterHeight, fighterX, fighterY, fighterHealth, fighterSpeed, fighterColor);
		}
		void initFighter(Fighter &fighter, int width, int height, int x, int y, int health, int speed, Color color) {
			fighter.Body.width = width;
			fighter.Body.height = height;
			fighter.Body.x = x;
			fighter.Body.y = y;
			fighter.Speed = speed;
			fighter.Health = health;
			fighter.Color = color;
			fighter.Active = true;
		}

		void drawFighter(Fighter fighter) {
			if (fighter.Active) {
				DrawRectangleRec(fighter.Body, fighter.Color);
			}
		}
		void moveFighter(Fighter &fighter) {
			float time = GetFrameTime();
			if (fighter.Active)
			{
				fighter.Body.x -= fighter.Speed*time;
			}
			if (fighter.Body.x <= 0 - fighter.Body.width) {
				fighter.Body.x = screenWidth + fighter.Body.x;
				fighter.Body.y = GetRandomValue(0, screenHeight - (screenHeight / 8)*1.1 - (fighter.Body.height/2));
			}
		}

	}
}