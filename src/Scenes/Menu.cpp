#include "Scenes\Menu.h"
#include "Objects\Window.h"
#include "System\Gamesystem.h"
#include "raylib.h"
namespace gamesystem {
	using namespace window;
	namespace menu {
		struct Cursor {
			Vector2 Position;
			int Radius = 10;
		};
		struct Button {
			Rectangle Body;
			Color Color;
		};
		Cursor cursor;
		Button play;
		Button exit;
		const int playWidth = 100;
		const int playHeight = 50;
		const int playY = screenHeight / 2 + playHeight;
		const int playX = screenWidth / 2 - playWidth / 2;
		const int exitWidth = 100;
		const int exitHeight = 50;
		const int exitY = screenHeight / 2 + exitHeight * 3;
		const int exitX = screenWidth / 2 - exitWidth / 2;
		const int fontSize = 20;
		const Color ButtonColor = RED;

		void update();
		void draw();
		void initButton(Button &button, int width, int height, int x, int y, Color color);
		void drawButton(Button button);
		void drawText();
		void followMenuCursor(Cursor &cursor);
		bool buttonIsClicked(Cursor cursor, Button button);
		void startGame(Cursor cursor, Button button, gamesystem::Gamestates &gamestate);
		void exitGame(Cursor cursor, Button button);

		void run() {
			update();
			draw();
		}
		void init() {
			initButton(play, playWidth, playHeight, playX, playY, ButtonColor);
			initButton(exit, exitWidth, exitHeight, exitX, exitY, ButtonColor);
		}
		void draw() {
			BeginDrawing();
			ClearBackground(BLACK);
			drawButton(play);
			drawButton(exit);
			drawText();
			EndDrawing();
		}
		void update() {
			followMenuCursor(cursor);
			exitGame(cursor, exit);
			startGame(cursor, play, gamesystem::Gamestate);
		}
		void initButton(Button &button, int width, int height, int x, int y, Color color) {
			button.Body.width = width;
			button.Body.height = height;
			button.Body.x = x;
			button.Body.y = y;
			button.Color = color;
		}
		void drawButton(Button button) {
			DrawRectangleRec(button.Body, button.Color);
		}
		void drawText() {
			DrawText("GRADIUS", GetScreenWidth() / 2 - (MeasureText("GRADIUS", fontSize / 2)), 30, fontSize, RAYWHITE);
			DrawText("PRESIONE 'PLAY' CUANDO ESTE LISTO PARA JUGAR.", GetScreenWidth() / 2 - (MeasureText("PRESIONE 'PLAY' CUANDO ESTE LISTO PARA JUGAR.", fontSize) / 2), 50, fontSize, RAYWHITE);
			DrawText("Use las flechas para moverse y espacio y B para disparar.", GetScreenWidth() / 2 - (MeasureText("Use las flechas para moverse y espacio y B para disparar.", fontSize) / 2), 100, fontSize, RAYWHITE);
			DrawText("PLAY", (static_cast<int>(play.Body.x) + static_cast<int>(play.Body.width) / 2) - (MeasureText("PLAY", fontSize) / 2),	(static_cast<int>(play.Body.y) + static_cast<int>(play.Body.height) / 2) - fontSize / 2, fontSize, RAYWHITE);
			DrawText("EXIT", (static_cast<int>(exit.Body.x) + static_cast<int>(exit.Body.width) / 2) - (MeasureText("EXIT", fontSize) / 2), (static_cast<int>(exit.Body.y) + static_cast<int>(exit.Body.height) / 2) - (fontSize / 2), fontSize, RAYWHITE);
			DrawText("Version 0.4", screenWidth - (MeasureText("Version 0.4", fontSize)), screenHeight - fontSize, fontSize, RAYWHITE);
		}
		void followMenuCursor(Cursor &cursor) {
			cursor.Position = GetMousePosition();
		}
		bool buttonIsClicked(Cursor cursor, Button button) {
			if (CheckCollisionCircleRec(cursor.Position, static_cast<float>(cursor.Radius), button.Body)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				return true;
			}
			else {
				return false;
			}
		}
		void exitGame(Cursor cursor, Button button) {
			if (buttonIsClicked(cursor, button)) {
				gamesystem::gameIsOn = false;
			}
		}
		void startGame(Cursor cursor, Button button, gamesystem::Gamestates &gamestate) {
			if (buttonIsClicked(cursor, button)) {
				gamestate = Game;
			}
		}
	}
}