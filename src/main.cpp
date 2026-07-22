#include "raylib.h"
#include "player.h"

int main() {
    // Create window
    const int screenWidth = 1000;
    const int screenHeight = 550;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Overcharge");

    // Set FPS
    SetTargetFPS(60);

    // Create player
    Player* player = new Player{100.f, 100.f};

    // Main loop
    while (!WindowShouldClose()) {
        // Game logic
        if (!IsWindowMaximized()) {
            SetWindowSize(screenWidth, screenHeight);
        }

        player->Update();

        // Drawings
        BeginDrawing();

            ClearBackground(DARKGRAY);
            player->Draw();

        EndDrawing();
    }

    // Delete player
    delete player;

    // Close window
    CloseWindow();

    return 0;
}