#include "Objects\Player.h"
#include "Objects\Window.h"
#include "raylib.h"
#include "Bomb.h"
#include "Bullets.h"
#include "Global/Global.h"

namespace gamesystem {
	using namespace window;
	namespace players {
		Player player;
		const Color playerColor = GRAY;
		const int playerWidth = 66;
		const int playerHeight = 30;
		const int playerX = screenWidth / 10;
		const int playerY = screenHeight / 2 - playerHeight / 2;
		const int playerSpeed = screenWidth;
		const int playerHealth = 1;
		const int bottomLimit = screenHeight - ((screenHeight / 8)*1.1);

		void initPlayer(Player &player, int width, int height, int x, int y, int lives, int speed, Color color);

		void init() {
			initPlayer(player, playerWidth, playerHeight, playerX, playerY, playerHealth, playerSpeed, playerColor);
		}
		void initPlayer(Player &player, int width, int height, int x, int y, int health, int speed, Color color) {
			player.Body.width = width;
			player.Body.height = height;
			player.Body.x = x;
			player.Body.y = y;
			player.Speed = speed;
			player.Health = health;
			player.Color = color;
		}

		void shootBullet(Bullets &bullet, Player player) {
			if (IsKeyDown(KEY_SPACE) && !bullet.Active) {
				bullet.Active = true;
				bullet.Body.x = player.Body.x + (player.Body.width / 2);
				bullet.Body.y = player.Body.y + (player.Body.height / 2);
			}
		}

		void shootBomb(Bombs &bomb, Player player) {
			if (IsKeyDown('B') && !bomb.Active) {
				bomb.Active = true;
				bomb.Body.x = player.Body.x + (player.Body.width / 2);
				bomb.Body.y = player.Body.y + (player.Body.height / 2);
			}
		}

		void drawPlayer(Player player) {
			DrawRectangleRec(player.Body, player.Color);
		}

		void drawPlayerAnim(Player player, Texture2D frame1, Texture2D frame2) {
			if (changeFrame()) {
				DrawTexture(frame1, player.Body.x - (player.Body.width / 2),
					player.Body.y - (player.Body.height / 10), WHITE);
			}
			else {
				DrawTexture(frame2, player.Body.x - (player.Body.width / 2),
					player.Body.y - (player.Body.height / 10), WHITE);
			}
		}

		void drawPlayerLives(Player player) {
			for (int i = 0; i < player.Health; i++) {
				DrawRectangle((i*player.Body.width), screenHeight / 10 - (player.Body.height * 2),
					player.Body.width / 2, player.Body.height / 2, player.Color);
			}
		}  

		void movePlayer(Player &player) {
			if (!pause) {
				float time = GetFrameTime();
				if (IsKeyDown(KEY_UP)) player.Body.y -= player.Speed*time;
				if ((player.Body.y) <= 0) player.Body.y = 1;
				if (IsKeyDown(KEY_DOWN)) player.Body.y += player.Speed*time;
				if ((player.Body.y + player.Body.height) >= bottomLimit) player.Body.y = bottomLimit - player.Body.height;
			}
		}
	}
}