#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/Window.h"
#include "System/Gamesystem.h"
using namespace players;
using namespace window;
using namespace gamesystem;
namespace gameplay {

	extern bool initOnce = true;
	
	void initFirstLevel();
	void input();
	void update();
	void draw();
	void drawPlayer(Player player);
	void drawPlayerLives(Player player);
	void movePlayer(Player &player);
	void checkWin(Player player, Gamestates &gamestate);
	
	void run() {
		if (initOnce) {
			initFirstLevel();
			initOnce = false;
		}
		input();
		update();
		draw();
	}
	void initFirstLevel() {
		
	}
	void input() {
		movePlayer(player);
	}
	void update() {
		
		checkWin(player, Gamestate);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawPlayerLives(player);
		EndDrawing();
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	void drawPlayerLives(Player player) {
		for (int i = 0; i < player.Health; i++) {
			DrawRectangle((i*player.Body.width), screenHeight - (player.Body.height * 2), player.Body.width / 2, player.Body.height / 2, player.Color);
		}
	}
	void movePlayer(Player &player) {
		float time = GetFrameTime();
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed*time;
		if ((player.Body.x) <= 0) player.Body.x = 1;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed*time;
		if ((player.Body.x + player.Body.width) >= screenHeight) player.Body.x = screenWidth - player.Body.width;
	}
	void checkWin(Player player, Gamestates &gamestate) {
	}
}