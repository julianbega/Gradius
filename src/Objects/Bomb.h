#ifndef BOMBS_H
#define BOMBS_H
#include "raylib.h"
namespace gamesystem {
	namespace bombs {
		struct Bombs {
			Rectangle Body;
			Color Color;
			float Speed;
			bool Active;
		};
		extern Bombs bomb;
		extern void init();
		void drawBomb(Bombs bomb);
		void moveBomb(Bombs &bomb);
	}
}
#endif

