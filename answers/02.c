#include "./raylib/include/raylib.h"

#define screen_size 720


int main() {

	float paddle_padding = 10.0;
	float paddle_width = 20.0;
	float paddle_height = 100.0;
	
	Rectangle paddle = {
		0 + paddle_padding, // I just put 0 here to represent that 0 is the left-most side and we are starting the paddle x to have some padding from that side 
		(float) screen_size / 2 - paddle_height/2,
		paddle_width,
		paddle_height,
	};

	InitWindow(720, 720, "Pong");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		// Frame Start

		// --- update gameplay / inputs
		if(IsKeyDown(KEY_W)) {
			paddle.y -= 20;
		}
		if(IsKeyDown(KEY_S)) {
			paddle.y += 20;
		}

		// --- start doing draw commands
		BeginDrawing();
		ClearBackground(GRAY);
		DrawLine(0, screen_size/2, screen_size, screen_size/2, LIGHTGRAY);

		DrawRectangleRec(paddle, WHITE);
		EndDrawing();
		
		// Frame End
	}
}