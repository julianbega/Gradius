#ifndef GROUNDFIGHTER_H
#define GROUNDFIGHTER_H
#include "raylib.h"

namespace groundFighters {

	struct GroundFighter {
		Rectangle Body;
		Color Color;
		int Health;
		int Speed;
		bool Active;
	};
	extern GroundFighter groundFighter;
	extern const int groundFighterHealth;
	void init();
}
#endif