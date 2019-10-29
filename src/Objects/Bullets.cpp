#include "Objects/Bullets.h"
#include "Objects/Window.h"
using namespace window;
namespace bullets {
	const int bulletWidth = 33;
	const int bulletHeight = 15;
	const int bulletSpeed = screenWidth/2;
	Color bulletColor = GRAY;
	Bullets bullet;
	void initBullets(Bullets &bullet,int width, int height, int speed,Color color);

	void init() {
		initBullets(bullet,bulletWidth,bulletHeight,bulletSpeed,bulletColor);
	}
	void initBullets(Bullets &bullet, int width, int height,
					 int speed, Color color){
		bullet.Body.height=height;
		bullet.Body.width=width;
		bullet.Color = color;
		bullet.Speed = speed;
		bullet.Active = false;
	}
}