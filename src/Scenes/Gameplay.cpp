#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/Window.h"
#include "System/Gamesystem.h"
using namespace players;
using namespace fighters;
using namespace window;
using namespace gamesystem;
namespace gameplay {

	extern bool initOnce = true;
	const int enemiesOnLevel = 10;
	int enemiesKilled=0;
	void init();
	void input();
	void update();
	void draw();
	void drawPlayer(Player player);
	void drawPlayerLives(Player player);
	void drawFighter(Fighter fighter);
	void movePlayer(Player &player);
	void moveFighter(Fighter &fighter);
	void checkPlayerEnemyCollision(Player &player, Fighter &fighter);
	void checkWinLose(Player player, Gamestates &gamestate);
	void run() {
		input();
		update();
		draw();
	}
	void gameplay::init() {

	}
	void input() {
		movePlayer(player);
	}
	void update() {
		moveFighter(fighter);
		checkPlayerEnemyCollision(player,fighter);
		checkWinLose(player, Gamestate);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawPlayerLives(player);
		drawFighter(fighter);
		EndDrawing();
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	void drawPlayerLives(Player player) {
		for (int i = 0; i < player.Health; i++) {
			DrawRectangle((i*player.Body.width), screenHeight/10 - (player.Body.height * 2),
							player.Body.width / 2, player.Body.height / 2, player.Color);
		}
	}
	void drawFighter(Fighter fighter) {
		if (fighter.Active) {
			DrawRectangleRec(fighter.Body, fighter.Color);
		}
	}
	void movePlayer(Player &player) {
		float time = GetFrameTime();
		if (IsKeyDown(KEY_UP)) player.Body.y -= player.Speed*time;
		if ((player.Body.y) <= 0) player.Body.y = 1;
		if (IsKeyDown(KEY_DOWN)) player.Body.y += player.Speed*time;
		if ((player.Body.y + player.Body.height) >= screenHeight) player.Body.y = screenHeight - player.Body.height;
	}
	void moveFighter(Fighter &fighter) {
		float time = GetFrameTime();
		if (fighter.Active)
		{
			fighter.Body.x -= fighter.Speed*time;
		}
		if (fighter.Body.x <= 0 - fighter.Body.width) {
			fighter.Body.x = screenWidth + fighter.Body.x;
			fighter.Body.y = GetRandomValue(0, screenHeight - fighter.Body.height);
		}
	}
	void checkPlayerEnemyCollision(Player &player, Fighter &fighter) {
		if (CheckCollisionRecs(player.Body,fighter.Body)&&fighter.Active){
			player.Health--;
			fighter.Active=false;
			enemiesKilled++;
		}
	}
	void checkWinLose(Player player, Gamestates &gamestate) {
		if (player.Health <= 0) {
			gamestate = Credits;
		}
		if (enemiesKilled == enemiesOnLevel) {
			gamestate = Credits;
		}
	}
}