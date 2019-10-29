#include "Objects\Player.h"
#include "Objects\Window.h"
using namespace window;
namespace players {
	Player player;
	const Color playerColor = GRAY;
	const int playerWidth = 66;
	const int playerHeight = 30;
	const int playerX = screenWidth / 10;
	const int playerY = screenHeight/2 - playerHeight/2;
	const int playerSpeed = screenWidth;
	const int playerHealth = 1;
	
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
}