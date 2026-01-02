// Add a second paddle for player 2

// Make it behave the same as player 1's paddle except that it is controlled with the 
// Up and Down on the keyboard instead of W and S

// This paddle should be placed on the right-most side with the same padding that player 1 has. 

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

		float screen_top_y = 0;
		bool is_paddle_out_of_top_screen_bounds = paddle.y < screen_top_y; 
		if (is_paddle_out_of_top_screen_bounds) {
			paddle.y = 0;
		}

		float screen_bottom_y = screen_size;
		bool is_paddle_out_of_bottom_screen_bounds = paddle.y + paddle.height > screen_bottom_y; 
		if (is_paddle_out_of_bottom_screen_bounds) {
			paddle.y = screen_bottom_y - paddle.height;
		}

		// --- start doing draw commands
		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleRec(paddle, WHITE);
		EndDrawing();
		
		// Frame End
	}
}