//
//
// Now make the ball move from the bottom of the screen to the top of the screen automatically.
// Make the ball "bounce" back and forth from the top to the bottom.
// 
// You can modify the speed to make it faster or slower - whatever is easier for you to debug and get it working

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

	float ball_size = 20;
	Rectangle ball = {
		(float)screen_size/2,
		(float) screen_size / 2 - ball_size/2,
		ball_size, 
		ball_size,
	};
	float ball_speed = 5.0;


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

		ball.y += ball_speed;
		float ball_top_y = ball.y;
		float ball_bottom_y = ball.y + ball.height;
		bool is_ball_top_out_of_bounds = ball_top_y < screen_top_y;
		if (is_ball_top_out_of_bounds) {
			ball.y = 0;
			ball_speed = -ball_speed;
		}
		bool is_ball_bottom_out_of_bounds = ball_bottom_y > screen_bottom_y;
		if (is_ball_bottom_out_of_bounds) {
			ball.y = screen_bottom_y - ball.height;
			ball_speed = -ball_speed;
		}

		// --- start doing draw commands
		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleRec(p1_paddle, WHITE);
		DrawRectangleRec(p2_paddle, WHITE);
		DrawRectangleRec(ball, PINK);


		EndDrawing();
		
		// Frame End
	}
}