#include "Objects\Window.h"
#include "raylib.h"
namespace gamesystem {
	namespace window {
		const int screenWidth = 800;
		const int screenHeight = 450;
		void init() {
			InitWindow(screenWidth, screenHeight, "Gradius");
		}
	}
}