#ifndef GROUNDFIGHTERBULLETS_H
#define GROUNDFIGHTERBULLETS_H
#include "raylib.h"
namespace groundFighterBullets {
	struct GroundFighterBullets {
		Rectangle Body;
		Color Color;
		float Speed;
		bool Active;
	};
	extern GroundFighterBullets groundFighterBullet;
	extern void init();
}
#endif

