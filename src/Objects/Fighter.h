#ifndef FIGHTER_H
#define FIGHTER_H
#include "raylib.h"
namespace fighters {
	struct Fighter {
		Rectangle Body;
		Color Color;
		int Health;
		int Speed;
		bool Active;
	};
	extern Fighter fighter;
	extern const int fighterHealth;
	void init();
	void drawFighter(Fighter fighter);
	void moveFighter(Fighter &fighter);
}
#endif