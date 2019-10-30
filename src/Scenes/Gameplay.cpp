#include "Objects/Player.h"
#include "Objects/Fighter.h"
#include "Objects/GroundFighter.h"
#include "Objects/Bullets.h"
#include "Objects/GroundFighterBullet.h"
#include "Objects/Bomb.h"
#include "Objects/Window.h"
#include "System/Gamesystem.h"
#include "Global/Global.h"
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
	const int parallaxWidth = screenWidth;
	const int parallaxHeight = screenHeight/8;
	const int parallaxSpeed = 300;
	extern bool initOnce = true;
	
	const int enemiesOnLevel = 1;

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
	
	void drawGroundFighter(GroundFighter groundFighter);
	void drawGroundFighterBullet(GroundFighterBullets groundFighterBullet);
	
	
	void controlPause(bool &pause);

	void moveGroundFighter(GroundFighter &groundFighter);
	void moveParallax(Rectangle &parallax);
	
	
	void moveGroundBullet(GroundFighterBullets &groundFighterBullet);
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
		players::shootBullet(bullet, player);
		players::shootBomb(bomb, player);
		players::movePlayer(player);
	}
	void update() {
		fighters::moveFighter(fighter);
		moveGroundFighter(groundFighter);
		moveParallax(parallax);
		bullets::moveBullet(bullet);
		moveGroundBullet(groundFighterBullet);
		bombs::moveBomb(bomb);
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
		bullets::drawBullet(bullet);
		bombs::drawBomb(bomb);
		players::drawPlayerAnim(player,frame1,frame2);
		players::drawPlayerLives(player);
		fighters::drawFighter(fighter);
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
		parallax.y = screenHeight - (parallaxHeight/2);
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
	void drawParallax(Rectangle parallax) {
		for (int i = 0; i < maxParallax / 2; i++) {
			DrawRectangle(GetRandomValue(0, 2*screenWidth), GetRandomValue(0, screenHeight), GetRandomValue(5, 10), 5 , parallaxColor);
		}
		for (int i = 0; i < maxParallax / 2; i++) {
			DrawRectangle(parallax.x, parallax.y, parallaxWidth, parallaxHeight, parallaxColor);
		}
		for (int i = 0; i < maxParallax / 2; i++) {
			DrawRectangle(parallax.x/2, parallax.y, parallaxWidth, parallaxHeight, GRAY);
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