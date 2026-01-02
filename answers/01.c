#include "./raylib/include/raylib.h"

#define screen_size 720


int main() {
	InitWindow(720, 720, "Pong");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		EndDrawing();
	}
}