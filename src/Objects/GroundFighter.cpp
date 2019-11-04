#include "Objects\GroundFighter.h"
#include "Objects\Window.h"
#include "Global/Global.h"
#include "Objects/Player.h"
#include "raylib.h"

namespace gamesystem {
	using namespace window;
	namespace groundFighters {

		const Color groundFighterColor = RED;
		const int groundFighterWidth = 20;
		const int groundFighterHeight = 10;
		const int groundFighterX = GetRandomValue(screenWidth + groundFighterWidth, screenWidth + 2 * groundFighterWidth);
		const int groundFighterY = screenHeight - groundFighterHeight;
		const int groundFighterSpeed = screenWidth / 2;
		const int groundFighterHealth = 1;
		GroundFighter groundFighter;

		void initGroundFighter(GroundFighter &groundFighter, int width, int height, int x, int y, int lives, int speed, Color color);

		void init() {
			initGroundFighter(groundFighter, groundFighterWidth, groundFighterHeight, groundFighterX, groundFighterY, groundFighterHealth, groundFighterSpeed, groundFighterColor);
		}
		void initGroundFighter(GroundFighter &groundFighter, int width, int height, int x, int y, int health, int speed, Color color) {
			groundFighter.Body.width = width;
			groundFighter.Body.height = height;
			groundFighter.Body.x = x;
			groundFighter.Body.y = y;
			groundFighter.Speed = speed;
			groundFighter.Health = health;
			groundFighter.Color = color;
			groundFighter.Active = true;
		}

		void moveGroundFighter(GroundFighter &groundFighter) {
			float time = GetFrameTime();
			if (groundFighter.Active)
			{
				groundFighter.Body.x -= groundFighter.Speed*time;
			}
			if (groundFighter.Body.x <= 0 - groundFighter.Body.width) {
				groundFighter.Body.x = screenWidth + groundFighter.Body.x;
				groundFighter.Body.y = screenHeight - groundFighter.Body.height;
			}
		}


		void moveGroundBullet(GroundFighterBullets &groundFighterBullet) {

			if (groundFighterBullet.Active) {
				float time = GetFrameTime();
				if (groundFighterBullet.Body.y >= groundShootCurve) {
					groundFighterBullet.Body.y -= groundFighterBullet.Speed*time;
				}
				if (groundFighterBullet.Body.y <= groundShootCurve) {
					groundFighterBullet.Body.x -= groundFighterBullet.Speed*time;
				}
			}
			if (groundFighterBullet.Body.x >= screenWidth + groundFighterBullet.Body.width) {
				groundFighterBullet.Active = false;
				groundShootCurve = 0;
			}
		}


		void shootGroundBullet(GroundFighterBullets &groundFighterBullet, GroundFighter groundFighter) {

			groundFighterBullet.Active = true;
			groundFighterBullet.Body.x = groundFighter.Body.x + (groundFighter.Body.width / 2);
			groundFighterBullet.Body.y = groundFighter.Body.y + (groundFighter.Body.height / 2);

		}

		void drawGroundFighterBullet(GroundFighterBullets groundFighterBullet) {
			if (groundFighterBullet.Active) {
				DrawRectangleRec(groundFighterBullet.Body, groundFighterBullet.Color);
			}
		}

		void drawGroundFighter(GroundFighter groundFighter) {
			if (groundFighter.Active) {
				DrawRectangleRec(groundFighter.Body, groundFighter.Color);
			}
		}


		void groundFighterShouldShoot(Player player) {
			if ((groundFighter.Body.x - groundFighter.Body.width / 2) > (player.Body.x + player.Body.width / 2)) {
				groundShootTimer += GetFrameTime();
			}
			if (groundShootTimer >= 2.3) {
				groundShootCurve = GetRandomValue(0 + player.Body.height, screenHeight - (3 * groundFighter.Body.height));
				shootGroundBullet(groundFighterBullet, groundFighter);
				groundShootTimer = 0;
			}
		}
	}
}