//
// First thing's first. Let's get a window displayed.
// In this one, I've set up the initial game loop with some annotations in the comments
//
// Change the color of the ClearBackground call 

#include "./raylib/include/raylib.h"

#define screen_size 720


int main() {
	// Initialize a Window, ready to be used
	InitWindow(screen_size, screen_size, "Pong");

	// Set the frame rate for the below loop to run at
	// Each iteration in the loop will be a constant ~16ms unless there is some issue
	// This is to ensure stable timing and frame rate
	SetTargetFPS(60);	

	while(!WindowShouldClose()) { // while the user doesn't exit the application keep iterating over the following code
		// Start of Frame
		BeginDrawing(); // <- Allow draw calls to start for this frame here
		ClearBackground(WHITE); // <- Clear the entire window to this color. If there was anything drawn on this window, they will be "erased". This is typically called before any other drawing functions
		EndDrawing(); // <- Display anything called after BeginDrawing
		// End of Frame
	}
}