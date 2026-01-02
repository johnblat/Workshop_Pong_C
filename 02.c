#include "./raylib/include/raylib.h"

#define screen_size 720

//
// Do the following:
// - Draw a "paddle" on the left side of the screen:
//    - The paddle should be represented with a rectangle of the following dimensions: 20 width x 100 height
//    - The paddle's starting position should be centered vertically
//    - The paddle should have 10 pixel padding from the leftmost side of the screen
//	  - Make the paddle whatever color you want
//
// - Move the paddle with the W and S keys for up and down movement respectively (we will reserve the Up and Down Keyboard keys for the right-side paddle)
//    - The paddle should move up and down at a reasonable speed so its not too fast and not too slow
//
// NOTE: I am drawing a line centered on the screen just so you can see if the paddle ends up being positioned correctly
//
// Run "build.bat answers\02" in the terminal to see the result

int main() {
	InitWindow(720, 720, "Pong");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		DrawLine(0, screen_size/2, screen_size, screen_size/2, LIGHTGRAY);

		EndDrawing();
	}
}