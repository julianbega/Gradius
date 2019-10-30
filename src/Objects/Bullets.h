#ifndef BULLETS_H
#define BULLETS_H
#include "raylib.h"
namespace bullets{
	struct Bullets{
		Rectangle Body;
		Color Color;
		float Speed;
		bool Active;
	};
	extern Bullets bullet;
	extern void init();
	void drawBullet(Bullets bullet);
	void moveBullet(Bullets &bullet);
}
#endif

