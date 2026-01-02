// Now it's time to get a ball going
// This is going to be the most complex part of what we are going in this game
// So, we're going to break it down in tiny iterations
//
// For the exercise, draw a ball that is a 20 width x 20 height rectangle
// Make the ball move at a speed of 2 across the screen from the left side of the screen to the right side.
//
// We will make the ball move faster in the future.
// In this exercise, the ball will leave the screen and never come back.

// Make the ball whatever color you want

#include "./raylib/include/raylib.h"

#define screen_size 720

int main() {

	float paddle_padding = 10.0;
	float paddle_width = 20.0;
	float paddle_height = 100.0;
	
	Rectangle p1_paddle = {
		paddle_padding, 
		(float) screen_size / 2 - paddle_height/2,
		paddle_width,
		paddle_height,
	};

	Rectangle p2_paddle = {
		screen_size - paddle_padding - paddle_width, 
		(float) screen_size / 2 - paddle_height/2,
		paddle_width,
		paddle_height,
	};


	InitWindow(720, 720, "Pong");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		// Frame Start

		{ // --- update  inputs
			if(IsKeyDown(KEY_W)) {
				p1_paddle.y -= 20;
			}
			if(IsKeyDown(KEY_S)) {
				p1_paddle.y += 20;
			}
			if (IsKeyDown(KEY_UP)) {
				p2_paddle.y -= 20;
			}
			if (IsKeyDown(KEY_DOWN)) {
				p2_paddle.y += 20;
			}
		}
			

		float screen_top_y = 0;
		float screen_bottom_y = screen_size;

		bool is_p1_out_of_top_screen_bounds = p1_paddle.y < screen_top_y; 
		if (is_p1_out_of_top_screen_bounds) {
			p1_paddle.y = 0;
		}

		bool is_p1_out_of_bottom_screen_bounds = p1_paddle.y + p1_paddle.height > screen_bottom_y; 
		if (is_p1_out_of_bottom_screen_bounds) {
			p1_paddle.y = screen_bottom_y - p1_paddle.height;
		}

		bool is_p2_out_of_top_screen_bounds = p2_paddle.y < screen_top_y; 
		if (is_p2_out_of_top_screen_bounds) {
			p2_paddle.y = 0;
		}

		bool is_p2_out_of_bottom_screen_bounds = p2_paddle.y + p2_paddle.height > screen_bottom_y; 
		if (is_p2_out_of_bottom_screen_bounds) {
			p2_paddle.y = screen_bottom_y - p2_paddle.height;
		}

		// --- start doing draw commands
		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleRec(p1_paddle, WHITE);
		DrawRectangleRec(p2_paddle, WHITE);

		EndDrawing();
		
		// Frame End
	}
}