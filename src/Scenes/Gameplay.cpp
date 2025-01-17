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

namespace gamesystem {
using namespace players;
using namespace fighters;
using namespace groundFighters;
using namespace groundFighterBullets;
using namespace window;
using namespace bullets;
using namespace bombs;
namespace gameplay {

	Rectangle parallax;
	Color parallaxColor = RAYWHITE;
	const int maxParallax = 22;
	const int ParallaxDistance = screenWidth / 3;
	const int parallaxWidth = screenWidth;
	const int parallaxHeight = screenHeight/8;
	const int ParallaxHeight2 = parallaxHeight / 11;
	const int parallaxSpeed = 300;
	extern bool initOnce = true;
	
	const int enemiesOnLevel = 1;

	
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
	void moveParallax(Rectangle &parallax);
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


	void init() {
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
		groundFighters::moveGroundFighter(groundFighter);
		moveParallax(parallax);
		bullets::moveBullet(bullet);
		groundFighters::moveGroundBullet(groundFighterBullet);
		bombs::moveBomb(bomb);
		checkPlayerEnemyCollision(player, fighter, groundFighter);
		checkPlayerEnemyBulletCollision(player, groundFighterBullet);
		hitEnemy(bullet, bomb, fighter, groundFighter);
		checkWinLose(player,bullet,Gamestate);
		groundFighters::groundFighterShouldShoot(player);
		
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
		groundFighters::drawGroundFighter(groundFighter);
		groundFighters::drawGroundFighterBullet(groundFighterBullet);
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
	
	
	void drawParallax(Rectangle parallax) {
		DrawRectangle(0, parallax.y/1.1, screenWidth , parallaxHeight*2, GRAY);
		int const StarY = parallax.y / 1.1;
		int const StarMinWith = 5;
		int const StarMaxWith = 10;
		int const StarHeight = 5;
		for (int i = 0; i < maxParallax / 2; i++) {
			DrawRectangle(GetRandomValue(0, 2*screenWidth), GetRandomValue(0, StarY), GetRandomValue(StarMinWith, StarMaxWith), StarHeight, WHITE);
		}

		for (int i = 0; i < maxParallax ; i++) {
			DrawRectangle(parallax.x, parallax.y+ parallaxHeight / 11, parallaxHeight / 3 , parallaxHeight, GREEN);
			DrawRectangle(parallax.x + ParallaxDistance  , parallax.y + ParallaxHeight2, parallaxHeight / 3, parallaxHeight, PURPLE);
			DrawRectangle(parallax.x + ParallaxDistance*2, parallax.y + ParallaxHeight2, parallaxHeight / 3, parallaxHeight, ORANGE);
			DrawRectangle(parallax.x + ParallaxDistance*3, parallax.y + ParallaxHeight2, parallaxHeight / 3, parallaxHeight, BROWN);
			DrawRectangle(parallax.x - ParallaxDistance  , parallax.y + ParallaxHeight2, parallaxHeight / 3, parallaxHeight, SKYBLUE);
		}
		
	}
	void moveParallax(Rectangle &parallax) {
		float time = GetFrameTime();
		parallax.x -= (parallaxSpeed * time)*2;
		if (parallax.x <= 0 - parallax.width) {
			parallax.x = screenWidth + ParallaxDistance;
		}
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
}