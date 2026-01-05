/**
*
 Now it so that when one player reaches 10 points, 
 it displays a separate screen with text that says
 "Player <num> Wins!"
 "Press Enter to Continue"
 And then it returns to the main menu 
*/
#include "./raylib/include/raylib.h"
#include <math.h>
#include <stdio.h>

#define screen_size 720

typedef enum Tag_App_State {
	AS_MAIN_MENU,
	AS_PLAYING
} App_State;


int main() {

	App_State app_state = AS_MAIN_MENU;

	float paddle_padding = 10.0;
	float paddle_width = 20.0;
	float paddle_height = 100.0;

	Rectangle p1_paddle_initial = {
		paddle_padding, 
		(float) screen_size / 2 - paddle_height/2,
		paddle_width,
		paddle_height,
	};
	
	Rectangle p1_paddle = p1_paddle_initial;

	int p1_score = 0;

	Rectangle p2_paddle_initial = {
		screen_size - paddle_padding - paddle_width, 
		(float) screen_size / 2 - paddle_height/2,
		paddle_width,
		paddle_height,
	};
	Rectangle p2_paddle = p2_paddle_initial;
	int p2_score = 0;

	float ball_size = 20;
	Rectangle ball_initial = {
		(float)screen_size/2,
		(float) screen_size / 2 - ball_size/2,
		ball_size, 
		ball_size,
	};
	Rectangle ball = ball_initial;
	
	float ball_speed = 10.0;

	float ball_direction_x = 1.0;
	float ball_direction_y = 0.0;


	InitWindow(720, 720, "Pong");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		// Frame Start

		if (app_state == AS_MAIN_MENU) {
			if (IsKeyPressed(KEY_ENTER)) {
				app_state = AS_PLAYING;
				p1_paddle = p1_paddle_initial;
				p2_paddle = p2_paddle_initial;
				ball = ball_initial;
				ball_direction_x = 1.0;
				ball_direction_y = 0.0;
			}
			BeginDrawing();
			ClearBackground(GRAY);
			DrawText("Pong", 10, 10, 40, WHITE);
			DrawText("Press Enter to Play", 10, 60, 30, WHITE);
			EndDrawing();
		} else if (app_state == AS_PLAYING) {
			if(IsKeyPressed(KEY_ENTER)) {
				app_state = AS_MAIN_MENU;
			}
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

			float ball_velocity_x = ball_direction_x*ball_speed;
			float ball_velocity_y = ball_direction_y*ball_speed;

			ball.x += ball_velocity_x;
			ball.y += ball_velocity_y;

			float ball_top_y = ball.y;
			float ball_bottom_y = ball.y + ball.height;
			bool is_ball_top_out_of_bounds = ball_top_y < screen_top_y;
			if (is_ball_top_out_of_bounds) {
				ball.y = 0;
				ball_direction_y = -ball_direction_y;
			}
			bool is_ball_bottom_out_of_bounds = ball_bottom_y > screen_bottom_y;
			if (is_ball_bottom_out_of_bounds) {
				ball.y = screen_bottom_y - ball.height;
				ball_direction_y = -ball_direction_y;
			}

			float ball_left_x = ball.x;
			float ball_right_x = ball.x + ball.width;

			bool went_in_p1_goal = ball_right_x < 0; // check the right side instead of left side of ball because we want to know if the ball is competely outside of the screen
			if (went_in_p1_goal) {
				ball.x = (float)screen_size/2;
				ball.y = (float)screen_size/2;
				ball_direction_x = -ball_direction_x;
				ball_direction_y = 0;
				p2_score += 1;
			}
			bool went_in_p2_goal = ball_left_x > screen_size; // check the right side instead of left side of ball because we want to know if the ball is competely outside of the screen
			if (went_in_p2_goal) {
				ball.x = (float)screen_size/2;
				ball.y = (float)screen_size/2;
				ball_direction_x = -ball_direction_x;			
				ball_direction_y = 0;

				p1_score += 1;
			}


			if (CheckCollisionRecs(p1_paddle, ball)) {
				Rectangle collision_rect = GetCollisionRec(p1_paddle, ball); 
				float collision_rect_mid_y = collision_rect.y + collision_rect.height/2;
				float relative_intersect_y = p1_paddle.y + (p1_paddle.height/2) - collision_rect_mid_y;
				float normalized_intersect_y = relative_intersect_y / (p1_paddle.height/2);
				float bounce_angle = normalized_intersect_y * (5*3.14/12);
				ball_direction_x = cosf(bounce_angle);
				ball_direction_y = -sinf(bounce_angle);

				ball.x = p1_paddle.x + p1_paddle.width;
			}

			if (CheckCollisionRecs(p2_paddle, ball)) {
				Rectangle collision_rect = GetCollisionRec(p2_paddle, ball); 
				float collision_rect_mid_y = collision_rect.y + collision_rect.height/2;
				float relative_intersect_y = p2_paddle.y + (p2_paddle.height/2) - collision_rect_mid_y;
				float normalized_intersect_y = relative_intersect_y / (p2_paddle.height/2);
				float bounce_angle = normalized_intersect_y * (5*3.14/12);
				ball_direction_x = -cosf(bounce_angle);
				ball_direction_y = -sinf(bounce_angle);

				ball.x = p2_paddle.x - ball.width;
			}
			
			// --- start doing draw commands
			BeginDrawing();
			ClearBackground(GRAY);

			Vector2 net_line_start = {(float)screen_size/2, 0};
			Vector2 net_line_end   = {(float)screen_size/2, (float)screen_size};
			DrawLineEx(net_line_start, net_line_end, 10, LIGHTGRAY);

			char p1_score_text[3];
			char p2_score_text[3];

			snprintf(p1_score_text, 3, "%d", p1_score);
			snprintf(p2_score_text, 3, "%d", p2_score);

			DrawText(p1_score_text, 20, 0, 40, LIGHTGRAY);
			int p2_score_text_width = MeasureText(p2_score_text, 40);
			DrawText(p2_score_text, screen_size - 20 - p2_score_text_width, 0, 40, LIGHTGRAY);

			DrawRectangleRec(p1_paddle, WHITE);
			DrawRectangleRec(p2_paddle, WHITE);
			DrawRectangleRec(ball, WHITE);


			EndDrawing();
		}		
	}
}