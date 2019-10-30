#include "Global/Global.h"
#include <iostream>
#include "raylib.h"

float timer = 0;
bool pause = false;
float groundShootTimer = 0;
float groundShootCurve = 0;

bool changeFrame() {
	timer += GetFrameTime();
	if (timer >= 0.25) {
		if (timer >= 0.5) {
			timer = 0;
		}
		return false;
	}
	else if (timer < 0.5) {
		return true;
	}
}

void controlPause(bool &pause) {

	if (IsKeyReleased(KEY_P)) {
		pause = !pause;
	}
}