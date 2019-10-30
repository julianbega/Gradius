#include "Global/Global.h"
#include <iostream>
#include "raylib.h"

float timer = 0;
bool pause = false;

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