#include "raylib.h"

int main() {
    // Create window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "GridDash");

    // Set FPS
    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose()) {
        // Game logic

        // Drawings
        BeginDrawing();

            ClearBackground(DARKGRAY);

        EndDrawing();
    }

    // Close window
    CloseWindow();

    return 0;
}