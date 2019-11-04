#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"

namespace gamesystem {

	extern bool pause;
	extern float timer;
	extern float groundShootTimer;
	extern float groundShootCurve;

	bool changeFrame();
	void controlPause(bool &pause);

	extern Music music;
	extern Sound shoot;

}
#endif 