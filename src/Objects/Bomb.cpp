#include "Objects/Bomb.h"
#include "Objects/Window.h"
#include "raylib.h"
using namespace window;
namespace bombs {
	const int bombHeight = 33;
	const int bombWidth = 15;
	const int bombSpeed = screenWidth / 2;
	Color bombColor = GRAY;
	Bombs bomb;
	void initBombs(Bombs &bomb, int width, int height, int speed, Color color);

	void init() {
		initBombs(bomb, bombWidth, bombHeight, bombSpeed, bombColor);
	}
	void initBombs(Bombs &bomb, int width, int height, int speed, Color color) {
		bomb.Body.height = height;
		bomb.Body.width = width;
		bomb.Color = color;
		bomb.Speed = speed;
		bomb.Active = false;
	}

	void drawBomb(Bombs bomb) {
		if (bomb.Active) {
			DrawRectangleRec(bomb.Body, bomb.Color);
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

}