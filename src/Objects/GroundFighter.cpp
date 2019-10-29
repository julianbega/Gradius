#include "Objects\GroundFighter.h"
#include "Objects\Window.h"
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
}