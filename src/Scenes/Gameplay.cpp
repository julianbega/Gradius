#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/GroundFighter.h"
#include "Objects/Bullets.h"
#include "Objects/GroundFighterBullet.h"
#include "Objects/Bomb.h"
#include "Objects/Window.h"
#include "System/Gamesystem.h"
#include <iostream>
using namespace players;
using namespace fighters;
using namespace groundFighters;
using namespace groundFighterBullets;
using namespace window;
using namespace bullets;
using namespace bombs;
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
	const int enemiesOnLevel = 1;
	float timer = 0;
	float groundShootTimer = 0;
	float groundShootCurve = 0;
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
	void drawGroundFighter(GroundFighter groundFighter);
	void drawGroundFighterBullet(GroundFighterBullets groundFighterBullet);
	void drawBullet(Bullets bullet);
	void drawBomb(Bombs bomb);
	void controlPause(bool &pause);
	void movePlayer(Player &player);
	void moveFighter(Fighter &fighter);
	void moveGroundFighter(GroundFighter &groundFighter);
	void moveParallax(Rectangle &parallax);
	void moveBullet(Bullets &bullet);
	void moveBomb(Bombs &bomb);
	void moveGroundBullet(GroundFighterBullets &groundFighterBullet);
	void shootBullet(Bullets &bullet, Player player);
	void shootBomb(Bombs &bomb, Player player);
	void shootGroundBullet(GroundFighterBullets &groundFighterBullet, GroundFighter groundFighter);
	void hitEnemy(Bullets &bullet, Bombs &bomb, Fighter &fighter, GroundFighter &groundFighter);
	void checkPlayerEnemyCollision(Player &player, Fighter &fighter, GroundFighter &groundFighter);
	void checkPlayerEnemyBulletCollision(Player &player, GroundFighterBullets &groundFighterBullet);
	void checkWinLose(Player player,Bullets bullet, Gamestates &gamestate);
	void run() {
		input();
		if (!pause){
			update();
		}
		draw();
	}
	void gameplay::init() {
		loadTextures(frame1, frame2);
		initParallax(parallax);
	}
	void input() {
		controlPause(pause);
		shootBullet(bullet, player);
		shootBomb(bomb, player);
		movePlayer(player);
	}
	void update() {
		moveFighter(fighter);
		moveGroundFighter(groundFighter);
		moveParallax(parallax);
		moveBullet(bullet);
		moveGroundBullet(groundFighterBullet);
		moveBomb(bomb);
		checkPlayerEnemyCollision(player, fighter, groundFighter);
		checkPlayerEnemyBulletCollision(player, groundFighterBullet);
		hitEnemy(bullet, bomb, fighter, groundFighter);
		checkWinLose(player,bullet,Gamestate);
		if ((groundFighter.Body.x - groundFighter.Body.width / 2) > (player.Body.x + player.Body.width / 2)) {
			groundShootTimer += GetFrameTime();
		}
		if (groundShootTimer >= 2.3){
			groundShootCurve = GetRandomValue(0 + player.Body.height, screenHeight - (3* groundFighter.Body.height));
			shootGroundBullet(groundFighterBullet, groundFighter);
			groundShootTimer = 0;
		}
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawParallax(parallax);
		drawBullet(bullet);
		drawBomb(bomb);
		drawPlayerAnim(player,frame1,frame2);
		drawPlayerLives(player);
		drawFighter(fighter);
		drawGroundFighter(groundFighter);
		drawGroundFighterBullet(groundFighterBullet);
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
	void drawBullet(Bullets bullet){
		if (bullet.Active) {
			DrawRectangleRec(bullet.Body, bullet.Color);
		}
	}
	void drawBomb(Bombs bomb) {
		if (bomb.Active) {
			DrawRectangleRec(bomb.Body, bomb.Color);
		}
	}
	void drawGroundFighterBullet(GroundFighterBullets groundFighterBullet) {
		if (groundFighterBullet.Active) {
			DrawRectangleRec(groundFighterBullet.Body, groundFighterBullet.Color);
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
	void drawGroundFighter(GroundFighter groundFighter) {
		if (groundFighter.Active) {
			DrawRectangleRec(groundFighter.Body, groundFighter.Color);
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

		if (IsKeyReleased(KEY_P)){
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

	void moveGroundFighter(GroundFighter &groundFighter) {
		float time = GetFrameTime();
		if (groundFighter.Active)
		{
			groundFighter.Body.x -= groundFighter.Speed*time;
		}
		if (groundFighter.Body.x <= 0 - groundFighter.Body.width) {
			groundFighter.Body.x = screenWidth + groundFighter.Body.x;
			groundFighter.Body.y = screenHeight - fighter.Body.height;
		}
	}
		
	void moveBullet(Bullets &bullet) {
		if (bullet.Active) {
			float time = GetFrameTime();
			bullet.Body.x += bullet.Speed*time;
		}
		if (bullet.Body.x >= screenWidth + bullet.Body.width) {
			bullet.Active = false;
		}
	}
	void moveBomb(Bombs &bomb) {
		if (bomb.Active) {
			float time = GetFrameTime();
			bomb.Body.y += bomb.Speed*time;
		}
		if (bomb.Body.y >= screenHeight + bomb.Body.width) {
			bomb.Active = false;
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

	void shootGroundBullet(GroundFighterBullets &groundFighterBullet, GroundFighter groundFighter) {
		
			groundFighterBullet.Active = true;
			groundFighterBullet.Body.x = groundFighter.Body.x + (groundFighter.Body.width / 2);
			groundFighterBullet.Body.y = groundFighter.Body.y + (groundFighter.Body.height / 2);
		
	}

	void hitEnemy(Bullets &bullet, Bombs &bomb, Fighter &fighter, GroundFighter &groundFighter) {
		if (CheckCollisionRecs(bullet.Body, fighter.Body) && bullet.Active) {
			bullet.Active = false;
			fighter.Active = false;
			enemiesKilled++;
		}
		if (CheckCollisionRecs(bullet.Body, groundFighter.Body) && bullet.Active) {
			bullet.Active = false;
			groundFighter.Active = false;
			enemiesKilled++;
		}
		if (CheckCollisionRecs(bomb.Body, fighter.Body) && bomb.Active) {
			bomb.Active = false;
			fighter.Active = false;
			enemiesKilled++;
		}
		if (CheckCollisionRecs(bomb.Body, groundFighter.Body) && bomb.Active) {
			bomb.Active = false;
			groundFighter.Active = false;
			enemiesKilled++;
		}
	}
	void checkPlayerEnemyCollision(Player &player, Fighter &fighter, GroundFighter &groundFighter) {
		if (CheckCollisionRecs(player.Body,fighter.Body)&&fighter.Active){
			player.Health--;
			fighter.Active=false;
			enemiesKilled++;
		}
		if (CheckCollisionRecs(player.Body, groundFighter.Body) && groundFighter.Active) {
			player.Health--;
			groundFighter.Active = false;
			enemiesKilled++;
		}
	}

	void checkPlayerEnemyBulletCollision(Player &player, GroundFighterBullets &groundFighterBullet) {
		if (CheckCollisionRecs(player.Body, groundFighterBullet.Body) && groundFighterBullet.Active) {
			player.Health--;
			groundFighterBullet.Active = false;
			enemiesKilled++;
		}
	}
	void checkWinLose(Player player,Bullets bullet, Gamestates &gamestate) {
		if (player.Health <= 0) {
			gamestate = Credits;
			bullet.Active = false;
		}
		if (enemiesKilled == enemiesOnLevel) {
			gamestate = Credits;
			enemiesKilled = 0;
		}
	}

}