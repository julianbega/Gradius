#include "Objects\Fighter.h"
#include "Objects\Window.h"
using namespace window;
namespace fighters {
	
	const Color fighterColor = RED;
	const int fighterWidth = 20;
	const int fighterHeight = 10;
	const int fighterX = GetRandomValue(screenWidth+fighterWidth , screenWidth + 2 * fighterWidth);
	const int fighterY = GetRandomValue(0,screenHeight-fighterHeight);
	const int fighterSpeed = screenWidth/2;
	const int fighterHealth = 1;
	Fighter fighter;

	void initFighter(Fighter &Fighter, int width, int height, int x, int y, int lives, int speed, Color color);

	void init() {
		initFighter(fighter, fighterWidth, fighterHeight, fighterX, fighterY, fighterHealth, fighterSpeed, fighterColor);
	}
	void initFighter(Fighter &fighter, int width, int height, int x, int y, int health, int speed, Color color) {
		fighter.Body.width = width;
		fighter.Body.height = height;
		fighter.Body.x = x;
		fighter.Body.y = y;
		fighter.Speed = speed;
		fighter.Health = health;
		fighter.Color = color;
		fighter.Active = true;
	}
}