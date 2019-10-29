#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/Window.h"
#include "System/Gamesystem.h"
using namespace players;
using namespace fighters;
using namespace window;
using namespace gamesystem;
namespace gameplay {

	Rectangle parallax;
	Color parallaxColor = RAYWHITE;
	const int maxParallax = 22;
	const int parallaxWidth = screenWidth / 20;
	const int parallaxHeight = screenHeight;
	const int parallaxSpeed = screenWidth / 30;
	extern bool initOnce = true;
	bool pause = false;
	const int enemiesOnLevel = 10;
	float timer = 0;
	int enemiesKilled = 0;
	Vector2 textureFrame = { player.Body.x,player.Body.y };
	Texture2D frame1;
	Texture2D frame2;

	void init();
	void input();
	void update();
	void draw();
	void loadTextures(Texture2D &frame1, Texture2D &frame2);
	void initParallax(Rectangle &parallax);
	void drawParallax(Rectangle parallax);
	void drawPlayer(Player player);
	void drawPlayerAnim(Player player, Texture2D frame1, Texture2D frame2);
	void drawPlayerLives(Player player);
	void drawFighter(Fighter fighter);
	void controlPause(bool &pause);
	void movePlayer(Player &player);
	void moveFighter(Fighter &fighter);
	void moveParallax(Rectangle &parallax);
	void checkPlayerEnemyCollision(Player &player, Fighter &fighter);
	void checkWinLose(Player player, Gamestates &gamestate);
	void run() {
		input();
		if (!pause){
			update();
			draw();
		}
	}
	void gameplay::init() {
		loadTextures(frame1, frame2);
		initParallax(parallax);
	}
	void input() {
		controlPause(pause);
		movePlayer(player);
	}
	void update() {
		moveFighter(fighter);
		moveParallax(parallax);
		checkPlayerEnemyCollision(player, fighter);
		checkWinLose(player, Gamestate);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawParallax(parallax);
		drawPlayer(player);
		drawPlayerAnim(player,frame1,frame2);
		drawPlayerLives(player);
		drawFighter(fighter);
		EndDrawing();
	}
	void loadTextures(Texture2D &frame1, Texture2D &frame2) {
		frame1 = LoadTexture("Resources/AnimFirstFrame.png");
		frame2 = LoadTexture("Resources/AnimSecFrame.png");
	}
	void initParallax(Rectangle &parallax) {
		parallax.width = parallaxWidth;
		parallax.height = parallaxHeight;
		parallax.x = 0;
		parallax.y = 0;
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	bool changeFrame() {
		timer += GetFrameTime();
		if (timer >= 0.25) {
			if (timer>=0.5){
				timer = 0;
			}
			return false;
		}
		else if (timer < 0.5) {
			return true;
		}
	}
	void drawPlayerAnim(Player player, Texture2D frame1, Texture2D frame2){
		if (changeFrame()){
			DrawTexture(frame1, player.Body.x - (player.Body.width / 2),
						player.Body.y - (player.Body.height / 10), WHITE);
		}
		else{
			DrawTexture(frame2, player.Body.x - (player.Body.width / 2),
				player.Body.y - (player.Body.height / 10), WHITE);
		}
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
	void drawParallax(Rectangle parallax) {
		for (int i = 0; i < maxParallax / 2; i++) {
			DrawRectangle(parallax.x - (i*parallax.width*2), parallax.y, parallax.width, parallax.height, parallaxColor);
		}
		for (int i = 0; i < maxParallax/2; i++) {
			DrawRectangle(parallax.x + (i*parallax.width*2), parallax.y, parallax.width, parallax.height, parallaxColor);
		}
	}
	void moveParallax(Rectangle &parallax) {
		float time = GetFrameTime();
		parallax.x -= parallaxSpeed * time;
		if (parallax.x <= 0 - parallax.width) {
			parallax.x = screenWidth + parallax.width;
		}
	}
	void controlPause(bool &pause) {
		if (IsKeyReleased(KEY_SPACE)) {
			pause = !pause;
		}
	}
	void movePlayer(Player &player) {
		if (!pause) {
			float time = GetFrameTime();
			if (IsKeyDown(KEY_UP)) player.Body.y -= player.Speed*time;
			if ((player.Body.y) <= 0) player.Body.y = 1;
			if (IsKeyDown(KEY_DOWN)) player.Body.y += player.Speed*time;
			if ((player.Body.y + player.Body.height) >= screenHeight) player.Body.y = screenHeight - player.Body.height;
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