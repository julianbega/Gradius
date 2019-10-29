#ifndef BOMBS_H
#define BOMBS_H
#include "raylib.h"
namespace bombs {
	struct Bombs {
		Rectangle Body;
		Color Color;
		float Speed;
		bool Active;
	};
	extern Bombs bomb;
	extern void init();
}
#endif

